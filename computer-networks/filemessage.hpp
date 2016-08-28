#ifndef FILEMESSAGE_HPP
#define FILEMESSAGE_HPP

#include <QFile>
#include <QString>
#include <QtGlobal>
#include <QFileInfo>
#include <QStringList>

#include "message.hpp"

class FileMessage : public Message
{
public:
    FileMessage(QFile *file, const QString &fromPeerId, bool isRead = true);
    FileMessage(const QString &filePath, const QString &fromPeerId, bool isRead = true);
    ~FileMessage();
    inline Message::Type type() {return Message::FILE;}
    inline QString contextData() const {return m_fileInfo->fileName();}
    qint64 numDataToSend() const;
    qint64 totalSize() const;
    qint64 nextSize() const;
    QByteArray nextByteArray();
    bool writeNextByteArray(QByteArray data);
    QString toString() const {return m_file->fileName();}
private:
    bool m_isRead;
    QFile *m_file;
    QFileInfo *m_fileInfo;
    qint64 m_sentData;
    void createOtherFile(const QString &fileName);
};

#endif // FILEMESSAGE_HPP
