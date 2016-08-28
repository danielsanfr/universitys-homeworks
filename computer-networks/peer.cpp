#include "peer.hpp"

#include <QDebug>
#include <QIODevice>
#include <QByteArray>

#include "Util.hpp"
#include "peermodel.hpp"
#include "filemessage.hpp"
#include "textmessage.hpp"
#include "pushanythingtcpsocket.hpp"

Peer::Peer(QObject *parent) : QTcpServer(parent),
    m_pendingListCount(0), m_hostAddress(Util::getIPv4HostAddress())
{
    // TODO Verificar se e possivel usar o QHostAddress::Any
    bool isOk = false;
    if (m_hostAddress.isNull())
        isOk = listen(QHostAddress::Any);
    else
        isOk = listen(m_hostAddress);
    Q_ASSERT(isOk);

    m_myPeer = new PeerModel(m_hostAddress, serverPort());
    m_announcer = new Announcer(m_myPeer, this);
    m_announcer->start();
    m_discoveryPeer = new DiscoveryPeer(m_myPeer, this);
    isOk = connect(m_discoveryPeer, SIGNAL(newPeerFound(PeerModel*)),
                   this, SLOT(onNewPeerFound(PeerModel*)));
    Q_ASSERT(isOk);
    isOk = connect(m_discoveryPeer, SIGNAL(newPeerFound(PeerModel*)),
                   this, SIGNAL(newPeerFound(PeerModel*)));
    Q_ASSERT(isOk);
    isOk = connect(m_discoveryPeer, SIGNAL(peerDead(QString)),
                   this, SIGNAL(peerDead(QString)));
    Q_ASSERT(isOk);
}

Peer::~Peer()
{
    delete m_myPeer;
    m_myPeer = 0;
}

const QList<PeerModel *> Peer::peerList() const
{
    return m_discoveryPeer->peerList();
}

void Peer::sendMessage(int type, const QString &source, const QString &peerId)
{
    switch ((Message::Type) type) {
    case Message::TEXT:
        m_pushAnything = new PushAnythingTcpSocket(new TextMessage(source, m_myPeer->id()), this);
        break;
    case Message::FILE:
        m_pushAnything = new PushAnythingTcpSocket(new FileMessage(source, m_myPeer->id()), this);
        break;
    default:
        m_pushAnything = 0;
        break;
    }
    if (m_pushAnything != 0) {
        PeerModel* peer = this->peer(peerId);
        if (peer != 0) {
            bool isOk = connect(m_pushAnything, SIGNAL(messageSent()),
                                this, SLOT(onMessageSent()));
            Q_ASSERT(isOk);
            isOk = connect(m_pushAnything, SIGNAL(error()),
                           this, SLOT(onErrorInMessageSent()));
            Q_ASSERT(isOk);
            m_pushAnything->connectToHost(peer->address(),
                                          peer->port(),
                                          QIODevice::WriteOnly);
            // we need to wait...
            if(!m_pushAnything->waitForConnected(1000)) {
                qDebug() << "Error: " << m_pushAnything->errorString();
            }
        }
    }
}

void Peer::incomingConnection(qintptr socketDescriptor)
{
    PullAnythingTcpSocket* pullAnything = new PullAnythingTcpSocket(m_pendingListCount, this);
    if(!(pullAnything->setSocketDescriptor(socketDescriptor)))
    {
        qDebug() << "Socket error!";
        return;
    }
    bool isOk = connect(pullAnything, SIGNAL(messageReceived(qint64,Message*)),
                        this, SLOT(onMessageReceived(qint64,Message*)));
    Q_ASSERT(isOk);
    isOk = connect(pullAnything, SIGNAL(error(qint64)),
                   this, SLOT(onErrorInMessageReceived(qint64)));
    Q_ASSERT(isOk);
    m_pendinglist.insert(m_pendingListCount, pullAnything);
    ++m_pendingListCount;
//    qDebug() << "Peer::incomingConnection" << m_pendinglist.size();
}

void Peer::onNewPeerFound(PeerModel * peerModel)
{
//    qDebug() << "Peer::onNewPeerFound" << peerModel->id();
//    m_pushAnything = new PushAnythingTcpSocket(new TextMessage("Testando o envio da primeira mensagem"), this);
//    m_pushAnything = new PushAnythingTcpSocket(new FileMessage("/home/daniel/test-rede/helloworld.c"), this);
//    m_pushAnything = new PushAnythingTcpSocket(new FileMessage("/home/daniel/LANChat.jar"), this);
//    m_pushAnything = new PushAnythingTcpSocket(new FileMessage("/home/daniel/Downloads/super_grub2_disk_hybrid_2.00s2.iso"), this);
//    m_pushAnything = new PushAnythingTcpSocket(new FileMessage("/home/daniel/Downloads/copy_agent-1.44.0357.tgz"), this);
//    m_pushAnything = new PushAnythingTcpSocket(new FileMessage(""), this);
}

void Peer::onMessageSent()
{
    qDebug() << "Peer::onMessageSent";
}

void Peer::onErrorInMessageSent()
{
    qDebug() << "Peer::onErrorInMessageSent";
}

void Peer::onMessageReceived(qint64 id, Message *messageReceived)
{
    qDebug() << "Peer::onMessageReceived" << id << messageReceived->toString();
    m_pendinglist.remove(id);
}

void Peer::onErrorInMessageReceived(qint64 id)
{
    m_pendinglist.remove(id);
    qDebug() << "Peer::onErrorInMessageReceived" << id;
}


