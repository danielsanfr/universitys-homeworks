#include "pullanythingtcpsocket.hpp"

#include <QDebug>
#include <QByteArray>

#include "Util.hpp"

PullAnythingTcpSocket::PullAnythingTcpSocket(qint64 id, QObject *parent) :
    QTcpSocket(parent), m_id(id), m_receivedDadaSize(0), m_currentMessage(0)
{
    bool isOk = connect(this, SIGNAL(readyRead()), SLOT(onReadyRead()));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
                   SLOT(onError(QAbstractSocket::SocketError)));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(disconnected()), SLOT(onDisconnected()));
    Q_ASSERT(isOk);
    isOk = connect(this, SIGNAL(disconnected()), SLOT(deleteLater()));
    Q_ASSERT(isOk);
}

QString PullAnythingTcpSocket::messageType() const
{
    return QString();
}

void PullAnythingTcpSocket::onReadyRead()
{
    while (bytesAvailable() > 0) {
        QByteArray data = read(Message::MAX_SIZE);
        if (m_currentMessage == 0) {
            if (data.mid(0, 8) == "[___[___") {
                m_headerBuffer.clear();
                m_receivedDadaSize = 0;
                QByteArray header = processHeader(data);
//                qDebug() << "Header received:" << header;
                m_currentMessage = Util::parse(header);
                if (m_currentMessage == 0)
                    m_headerBuffer.append(data);
                else {
                    data = data.mid(header.size() + 18);
                    if (data.size() > 0)
                        m_currentMessage->writeNextByteArray(data);
                }
            } else {
                m_headerBuffer.append(data);
                QByteArray header = processHeader(m_headerBuffer);
//                qDebug() << "Header received:" << header;
                m_currentMessage = Util::parse(header);
                if ((m_currentMessage != 0)) {
                    data = m_headerBuffer.mid(header.size() + 18);
                    if (data.size() > 0)
                        m_currentMessage->writeNextByteArray(data);
                }
            }
        } else {
            m_currentMessage->writeNextByteArray(data);
        }
        m_receivedDadaSize += data.size();
    }
}

void PullAnythingTcpSocket::onError(QAbstractSocket::SocketError socketError)
{
    if (socketError != RemoteHostClosedError || m_currentMessage == 0 ||
            m_currentMessage->totalSize() != m_receivedDadaSize) {
        delete m_currentMessage;
        m_currentMessage = 0;
    }
}

void PullAnythingTcpSocket::onDisconnected()
{
    if (m_currentMessage == 0)
        emit error(m_id);
    else
        emit messageReceived(m_id, m_currentMessage);
//    delete m_currentMessage;
    m_currentMessage = 0;
}

QByteArray PullAnythingTcpSocket::processHeader(QByteArray data)
{
    qint64 size = data.size() - 8;
    QByteArray buffe;
    for (qint64 i = 9; i < size; ++i) {
        if (data.mid(i, 9) == " ___]___]") {
            return buffe;
            break;
        }
        buffe += data.mid(i, 1);
    }
    return QByteArray();
}

