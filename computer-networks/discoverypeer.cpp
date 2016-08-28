#include "discoverypeer.hpp"

#include <QStringList>

DiscoveryPeer::DiscoveryPeer(PeerModel *peerModel, QObject *parent) :
    QObject(parent), m_port(42424), m_timeToLive(new QTimer(this)), m_udpSocket(new QUdpSocket(this)),
    m_groupAddress(QHostAddress("239.242.42.42")),//("239.255.43.21")
    m_peerModel(QSharedPointer<PeerModel>(peerModel))
{
    // Create a new UDP socket and bind it against port 42424
    m_udpSocket = new QUdpSocket(this);
    m_udpSocket->bind(QHostAddress::AnyIPv4, m_port, QUdpSocket::ShareAddress);

    /*
     * Create signal/slot connection to invoke processPendingDatagrams() whenever
     * a new multicast datagram is received by the socket.
     */
    bool isOk = connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    Q_ASSERT(isOk);

    // Tell the UDP socket which multicast group it should join
    m_udpSocket->joinMulticastGroup(m_groupAddress);
    isOk = connect(m_timeToLive, SIGNAL(timeout()), this, SLOT(whoIsAlive()));
    Q_ASSERT(isOk);
    m_timeToLive->start(4500);
}

const QList<PeerModel *> DiscoveryPeer::peerList() const
{
    return m_peerHash.values();
}

void DiscoveryPeer::processPendingDatagrams()
{
    // Now read all available datagrams from the socket
    while (m_udpSocket->hasPendingDatagrams()) {
        // Create a temporary buffer ...
        QByteArray datagram;

        // ... with the size of the received multicast datagram ...
        datagram.resize(m_udpSocket->pendingDatagramSize());

        QHostAddress senderAddress;
        // ... and copy over the received multicast datagram into that buffer.
        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress);

        QString data(datagram.data());
        QStringList dataStringList = data.split(" ");
        if (data.startsWith("[___[___HELLO") && data.endsWith("___]___]") && dataStringList.size() == 4) {
            bool isOk = false;
            qint64 port = dataStringList.at(2).toInt(&isOk);
            if (isOk) {
                PeerModel *newPeer= new PeerModel(senderAddress,
                                                  port,
                                                  dataStringList.at(1));
                if (*newPeer != *m_peerModel) {
                    if (m_peerHash.contains(newPeer->id())) {
                        m_peerHash.value(newPeer->id())->setLastHeartbeat(QTime::currentTime());
                        delete newPeer;
                        newPeer = 0;
                    } else {
                        m_peerHash.insert(newPeer->id(), newPeer);
                        emit newPeerFound(newPeer);
                    }
                }
            }
        } else if (data.startsWith("[___[___BYEBYE") && data.endsWith("___]___]")) {
            removePeer(dataStringList.at(1));
            emit peerDead(dataStringList.at(1));
        }
//        qDebug() << m_peerHash.keys();
//        qDebug() << tr("Received datagram: \"%1\"").arg(datagram.data()) << senderAddress.toString();
    }
}

void DiscoveryPeer::whoIsAlive()
{
    QTime currentTime = QTime::currentTime();
    QList<QString> keys = m_peerHash.keys();
    foreach (QString key, keys) {
        if (m_peerHash.value(key)->lastHeartbeat().secsTo(currentTime) >= 5) {
            emit peerDead(key);
            removePeer(key);
        }
    }
}

void DiscoveryPeer::removePeer(const QString &id)
{
    PeerModel *peerModel = m_peerHash.value(id);
    delete peerModel;
    m_peerHash.remove(id);
}
