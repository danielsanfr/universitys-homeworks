#ifndef TEXTMESSAGE_HPP
#define TEXTMESSAGE_HPP

#include <QString>

#include "message.hpp"

class TextMessage : public Message
{
public:
    explicit TextMessage();
    explicit TextMessage(const QString &message, const QString &fromPeerId);
    inline Type type() {return Message::TEXT;}
    qint64 numDataToSend() const;
    qint64 totalSize() const;
    qint64 nextSize() const;
    QByteArray nextByteArray();
    bool writeNextByteArray(QByteArray data);
    QString toString() const {return m_message;}
private:
    bool m_isRead;
    QString m_message;
};

#endif // TEXTMESSAGE_HPP
