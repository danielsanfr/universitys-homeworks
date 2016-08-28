#ifndef PULLANYTHINGTCPSOCKET_HPP
#define PULLANYTHINGTCPSOCKET_HPP

#include <QTcpSocket>
#include <QtGlobal>

#include "message.hpp"

class PullAnythingTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit PullAnythingTcpSocket(qint64 id, QObject *parent = 0);
    QString messageType() const;
signals:
    void messageReceived(qint64, Message *);
    void error(qint64);
private slots:
    void onReadyRead();
    void onError(QAbstractSocket::SocketError);
    void onDisconnected();
private:
    qint64 m_id;
    qint64 m_receivedDadaSize;
    Message *m_currentMessage;
    QByteArray m_headerBuffer;
    QByteArray processHeader(QByteArray data);
};

#endif // PULLANYTHINGTCPSOCKET_HPP
