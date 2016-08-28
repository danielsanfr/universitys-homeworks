#include "announcer.hpp"

#include <QDebug>
#include <QByteArray>

#include "byebyemessage.hpp"
#include "announcesmessage.hpp"

Announcer::Announcer(PeerModel *peerModel, QObject *parent) :
    QObject(parent), m_port(42424), m_udpSocket(new QUdpSocket(this)),
    m_heartbeatTimer(new QTimer(this)),
    m_groupAddress(QHostAddress("239.242.42.42")),//("239.255.43.21");
    m_peerModel(QSharedPointer<PeerModel>(peerModel))
{
    // Set it on the multicast UDP socket.
    m_udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    /**
     * Create a signal/slot connection so that whenever the timer times out, the sendDatagram()
     * method is invoked.
     */
    bool isOk = connect(m_heartbeatTimer, SIGNAL(timeout()), this, SLOT(heartbeat()));
    Q_ASSERT(isOk);
}

Announcer::~Announcer()
{
    byebye();
}

void Announcer::start()
{
    m_heartbeatTimer->singleShot(1, this, SLOT(heartbeat()));
    m_heartbeatTimer->start(2000);
}

void Announcer::stop()
{
    byebye();
}

void Announcer::heartbeat()
{
    const QByteArray datagram = QByteArray("[___[___HELLO " + m_peerModel->id().toUtf8() + ' ' + QByteArray::number(m_peerModel->port()) + " ___]___]");
    // Send the multicast datagram with the given content to port m_port
//    qDebug() <<
                m_udpSocket->writeDatagram(datagram.data(), datagram.size(), m_groupAddress, m_port);
//    qDebug() << m_udpSocket->errorString();
}

void Announcer::byebye()
{
    const QByteArray datagram = QByteArray("[___[___BYEBYE " + m_peerModel->id().toUtf8() + " ___]___]");
    // Send the multicast datagram with the given content to port m_port
    m_udpSocket->writeDatagram(datagram.data(), datagram.size(), m_groupAddress, m_port);
}
