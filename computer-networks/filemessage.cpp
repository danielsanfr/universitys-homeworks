#include "filemessage.hpp"

#include <QDebug>

FileMessage::FileMessage(QFile *file, const QString &fromPeerId, bool isRead) :
    Message(fromPeerId), m_file(file), m_fileInfo(new QFileInfo(*m_file))
{
    m_sentData = 0;
    m_isRead = isRead;
    if (isRead)
        m_file->open(QFile::ReadOnly);
    else {
        if (m_file->exists()) {
            QString filePath = m_file->fileName();
            createOtherFile(filePath);
        }
        m_file->open(QFile::WriteOnly);
    }
}

FileMessage::FileMessage(const QString &filePath, const QString &fromPeerId, bool isRead) :
    Message(fromPeerId), m_file(new QFile(filePath)), m_fileInfo(new QFileInfo(filePath))
{
    m_sentData = 0;
    m_isRead = isRead;
    if (isRead)
        m_file->open(QFile::ReadOnly);
    else {
        if (m_file->exists())
            createOtherFile(filePath);
        m_file->open(QFile::WriteOnly);
    }
}

FileMessage::~FileMessage()
{
    m_file->close();
    delete m_file;
    delete m_fileInfo;
}

qint64 FileMessage::numDataToSend() const
{
    return 1;
}

qint64 FileMessage::totalSize() const
{
    return m_fileInfo->size();
}

qint64 FileMessage::nextSize() const
{
    return m_fileInfo->size();
}

QByteArray FileMessage::nextByteArray()
{
    if (m_sentData == totalSize())
        return QByteArray();
    m_sentData += MAX_SIZE;
    QByteArray nextPackage;
//    nextPackage.resize(MAX_SIZE);
    nextPackage = m_file->read(MAX_SIZE);
    return nextPackage;
}

bool FileMessage::writeNextByteArray(QByteArray data)
{
    if (!(m_file->write(data, data.size()) == data.size()))
        return false;
    return m_file->flush();
}

void FileMessage::createOtherFile(const QString &fileName)
{
    m_file->close();
    delete m_file;
    delete m_fileInfo;
    QStringList fileNamePars = fileName.split(".");
    QString lastText = fileNamePars.at(fileNamePars.size() - 2);
    fileNamePars.removeAt(fileNamePars.size() - 2);
    fileNamePars.insert(fileNamePars.size() - 1, lastText+ " (copy)");
    m_file = new QFile(fileNamePars.join("."));
    m_fileInfo = new QFileInfo(fileNamePars.join("."));
    if (m_file->exists())
        createOtherFile(m_file->fileName());
}
