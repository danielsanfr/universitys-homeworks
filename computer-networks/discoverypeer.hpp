#ifndef DISCOVERYPEER_HPP
#define DISCOVERYPEER_HPP

#include <QList>
#include <QHash>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <QPointer>
#include <QtGlobal>
#include <QUdpSocket>
#include <QHostAddress>
#include <QSharedPointer>

#include "peermodel.hpp"

class DiscoveryPeer : public QObject
{
    Q_OBJECT
public:
    explicit DiscoveryPeer(PeerModel *peerModel, QObject *parent = 0);
    const QList<PeerModel *> peerList() const;
    inline PeerModel *peer(const QString &id) {return m_peerHash.value(id, 0);}
signals:
    void newPeerFound(PeerModel *);
    void peerDead(QString);
private slots:
    void processPendingDatagrams();
    void whoIsAlive();
private:
    qint16 m_port;
    QTimer *m_timeToLive;
    QUdpSocket *m_udpSocket;
    QHostAddress m_groupAddress;
    QSharedPointer<PeerModel> m_peerModel;
    QHash<QString, PeerModel* > m_peerHash;
    void removePeer(const QString &id);
};

#endif // DISCOVERYPEER_HPP
