#ifndef PEERMODEL_HPP
#define PEERMODEL_HPP

#include <QTime>
#include <QString>
#include <QtGlobal>
#include <QHostAddress>

class PeerModel
{
public:
    explicit PeerModel(QHostAddress address, quint16 port);
    explicit PeerModel(QHostAddress address, quint16 port, QString id);
    QString id() const;
    void setId(const QString &id);
    quint16 port() const;
    void setPort(const quint16 &port);
    QHostAddress address() const;
    void setAddress(const QHostAddress &address);
    QTime lastHeartbeat() const;
    void setLastHeartbeat(const QTime &lastHeartbeat);
    const QString toString() const;
    bool equals(PeerModel *otherPeerModel);
    bool operator ==(const PeerModel &otherPeerModel);
    bool operator !=(const PeerModel &otherPeerModel);

private:
    QString m_id;
    quint16 m_port;
    QHostAddress m_address;
    QTime m_lastHeartbeat;
};

#endif // PEERMODEL_HPP
