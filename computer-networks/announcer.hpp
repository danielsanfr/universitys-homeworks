#ifndef ANNOUNCER_HPP
#define ANNOUNCER_HPP

#include <QTimer>
#include <QObject>
#include <QtGlobal>
#include <QUdpSocket>
#include <QHostAddress>
#include <QSharedPointer>

#include "peermodel.hpp"

class Announcer : public QObject
{
    Q_OBJECT
public:
    explicit Announcer(PeerModel *peerModel, QObject *parent = 0);
    ~Announcer();
    void start();
    void stop();
signals:
private slots:
    void heartbeat();
private:
    qint16 m_port;
    QUdpSocket *m_udpSocket;
    QTimer *m_heartbeatTimer;
    QHostAddress m_groupAddress;
    QSharedPointer<PeerModel> m_peerModel;
    void byebye();
};

#endif // ANNOUNCER_HPP
