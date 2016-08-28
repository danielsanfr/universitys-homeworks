#include "textmessage.hpp"

TextMessage::TextMessage() : Message(""), m_isRead(false)
{
}

TextMessage::TextMessage(const QString &message, const QString &fromPeerId) :
     Message(fromPeerId), m_isRead(true), m_message(message)
{
}

qint64 TextMessage::numDataToSend() const
{
    return 1;
}

qint64 TextMessage::totalSize() const
{
    return m_message.toUtf8().size();
}

qint64 TextMessage::nextSize() const
{
    return totalSize();
}

QByteArray TextMessage::nextByteArray()
{
    return m_message.toUtf8();
}

bool TextMessage::writeNextByteArray(QByteArray data)
{
    if (!m_isRead)
        m_message += QString(data);
    return !m_isRead;
}
