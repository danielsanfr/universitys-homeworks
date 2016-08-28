#ifndef PUSHANYTHINGTCPSOCKET_HPP
#define PUSHANYTHINGTCPSOCKET_HPP

#include <QtGlobal>
#include <QTcpSocket>

#include "message.hpp"

class PushAnythingTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit PushAnythingTcpSocket(Message *message, QObject *parent = 0);
signals:
    void messageSent();
    void error();
private slots:
    void sendMetaData();
    void sendData(qint64);
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
private:
    bool m_hasError;
    qint64 m_dataSizeSent;
    qint64 m_totalSizeToSend;
    Message *m_currentMessage;
    void closeConnection();
};

#endif // PUSHANYTHINGTCPSOCKET_HPP
