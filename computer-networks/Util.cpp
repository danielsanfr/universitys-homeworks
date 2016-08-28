#include "Util.hpp"

#include <QDebug>
#include <QtGlobal>
#include <QIODevice>
#include <QStringList>
#include <QDataStream>
#include <QNetworkInterface>
#include <QCryptographicHash>

#include "filemessage.hpp"
#include "textmessage.hpp"

namespace Util {

QString getUid()
{
    return QString();
}

/* For more informations see:
 * http://stackoverflow.com/questions/7609953/obtaining-mac-address-on-windows-in-qt
 */
QString getFirstMacAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack) && (netInterface.flags() & QNetworkInterface::IsRunning) && (netInterface.flags() & QNetworkInterface::IsUp))
            return netInterface.hardwareAddress();
    }
    return QString();
}

QHostAddress getIPv4HostAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack) && (netInterface.flags() & QNetworkInterface::IsRunning) && (netInterface.flags() & QNetworkInterface::IsUp))
            return QHostAddress(netInterface.addressEntries().at(0).ip().toString());
        // if use "at(1)" you get ipv6
    }
    return QHostAddress();
}

QString encodeToMd5(const QString& text)
{
    return QString(QCryptographicHash::hash(text.toUtf8(),
            QCryptographicHash::Md5).toHex());
}

// For more informations see: http://stackoverflow.com/questions/1251662/qbytearray-to-integer
qint32 byteArrayToInt32(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}

Message *parse(QByteArray header) {
    QStringList part = QString(header).trimmed().split(" ");
    if (part.size() < 5 || part.size() > 6)
        return 0;
    bool isOk = false;
    Message::Type type = (Message::Type) part[2].toInt(&isOk);
    if (!isOk)
        return 0;
    switch (type) {
    case Message::TEXT:
        return new TextMessage();
    case Message::FILE:
        return new FileMessage(part[3], "", false);
    default:
        return 0;
    }
}

}
