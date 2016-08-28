#include "pushanythingtcpsocket.hpp"

#include <QDebug>
#include <QByteArray>

#include <textmessage.hpp>

PushAnythingTcpSocket::PushAnythingTcpSocket(Message *message, QObject *parent) :
    QTcpSocket(parent), m_hasError(false), m_currentMessage(message)
{
    bool isOk = connect(this, SIGNAL(connected()),
                        SLOT(sendMetaData()));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(disconnected()),
                   SLOT(onDisconnected()));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(disconnected()),
                   SLOT(deleteLater()));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
                   SLOT(onError(QAbstractSocket::SocketError)));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(bytesWritten(qint64)),
                        this, SLOT(sendData(qint64)));
    Q_ASSERT(isOk);
}

void PushAnythingTcpSocket::sendMetaData()
{
    m_dataSizeSent = 0;
    m_totalSizeToSend = m_currentMessage->header().size() + m_currentMessage->totalSize();
    write(m_currentMessage->header());
}

void PushAnythingTcpSocket::sendData(qint64 bytes)
{
    m_dataSizeSent += bytes;
    if (m_dataSizeSent == m_totalSizeToSend) {
        qDebug() << "Finish send";
        closeConnection();
        return;
    } else if (m_dataSizeSent > m_totalSizeToSend) {
        qDebug() << "Error send";
        closeConnection();
        return;
    }
    write(m_currentMessage->nextByteArray());
}

void PushAnythingTcpSocket::onDisconnected()
{
    if (m_dataSizeSent == m_totalSizeToSend)
        emit messageSent();
    else
        emit error();
}

void PushAnythingTcpSocket::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    emit error();
}

void PushAnythingTcpSocket::closeConnection()
{
    delete m_currentMessage;
    m_currentMessage = 0;
//    disconnect();
    disconnectFromHost();
    if (state() != QTcpSocket::UnconnectedState)
        waitForDisconnected(1000);
    close();
}
