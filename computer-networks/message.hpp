#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <QtGlobal>
#include <QByteArray>

class Message
{
public:
    static const qint64 MAX_SIZE = 10000;
    enum Type {
        UNKNOWN,
        BYEBYE,
        ANNOUNCE,
        JOIN,
        REFUSE,
        ACCEPT,
        TEXT,
        FILE
    };
    // RECEIVE
    explicit Message(const QString &fromPeerId) {m_fromPeerId = fromPeerId.toUtf8();}
    virtual ~Message() {}
    inline QByteArray header() {
        QByteArray header;
        header += QByteArray("[___[___ ") + QByteArray::number(numDataToSend())
                + ' ' + QByteArray::number(totalSize())
                + ' ' + QByteArray::number(type());
        if(!contextData().isEmpty())
            header += ' ' + contextData().toUtf8();
        header += ' ' + QByteArray::number(nextSize())
                + ' ' + m_fromPeerId
                + QByteArray(" ___]___]");
        return header;
    }
    inline virtual Message::Type type() {return Message::UNKNOWN;}
    inline virtual QString contextData() const {return QString();}
    virtual qint64 numDataToSend() const = 0;
    virtual qint64 totalSize() const = 0;
    virtual qint64 nextSize() const = 0;
    virtual QByteArray nextByteArray() = 0;
    inline virtual bool writeNextByteArray(QByteArray data) {Q_UNUSED(data);return true;}
    inline virtual QString toString() const {return QString("UNKNOWN");}
protected:
    QByteArray m_fromPeerId;
};

#endif // MESSAGE_HPP
