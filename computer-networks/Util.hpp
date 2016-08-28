#ifndef UTIL_HPP
#define UTIL_HPP

#include <QString>
#include <QHostAddress>

#include "message.hpp"

namespace Util {
    QString getUid();
    QString getFirstMacAddress();
    QHostAddress getIPv4HostAddress();
    QString encodeToMd5(const QString& text);
    qint32 byteArrayToInt32(QByteArray source);
    Message *parse(QByteArray header);
}

#endif // UTIL_HPP
