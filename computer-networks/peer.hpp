#ifndef PEER_HPP
#define PEER_HPP

#include <QList>
#include <QHash>
#include <QObject>
#include <QString>
#include <QtGlobal>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSharedPointer>

#include "announcer.hpp"
#include "discoverypeer.hpp"
#include "pushanythingtcpsocket.hpp"
#include "pullanythingtcpsocket.hpp"

class Peer : public QTcpServer
{
    Q_OBJECT
public:
    explicit Peer(QObject *parent = 0);
    ~Peer();
    const QList<PeerModel * > peerList() const;
    inline PeerModel *myPeer() {return m_myPeer;}
    inline PeerModel *peer(const QString &id) {return m_discoveryPeer->peer(id);}
public slots:
    void sendMessage(int type, const QString &source, const QString &peerId);
signals:
    void newPeerFound(PeerModel *);
    void peerDead(QString);
protected:
    void incomingConnection(qintptr socketDescriptor);
private slots:
    void onNewPeerFound(PeerModel *);
    void onMessageSent();
    void onErrorInMessageSent();
    void onMessageReceived(qint64, Message *);
    void onErrorInMessageReceived(qint64);
private:
    PeerModel *m_myPeer;
    qint64 m_pendingListCount;
    Announcer *m_announcer;
    DiscoveryPeer *m_discoveryPeer;
    QHostAddress m_hostAddress;
    PushAnythingTcpSocket *m_pushAnything;
    QHash<qint64, PullAnythingTcpSocket* > m_pendinglist;
};

#endif // PEER_HPP
