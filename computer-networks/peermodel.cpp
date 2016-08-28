#include "peermodel.hpp"

#include <QUuid>

#include "Util.hpp"

PeerModel::PeerModel(QHostAddress address, quint16 port) :
    m_port(port), m_address(address), m_lastHeartbeat(QTime::currentTime())
{
    m_id = Util::encodeToMd5(Util::getFirstMacAddress()) + ":"
            + Util::encodeToMd5(QUuid::createUuid().toString());
}

PeerModel::PeerModel(QHostAddress address, quint16 port, QString id):
    m_id(id), m_port(port), m_address(address), m_lastHeartbeat(QTime::currentTime())
{
}

QString PeerModel::id() const
{
    return m_id;
}

void PeerModel::setId(const QString &id)
{
    m_id = id;
}

quint16 PeerModel::port() const
{
    return m_port;
}

void PeerModel::setPort(const quint16 &port)
{
    m_port = port;
}
QHostAddress PeerModel::address() const
{
    return m_address;
}

void PeerModel::setAddress(const QHostAddress &address)
{
    m_address = address;
}

QTime PeerModel::lastHeartbeat() const
{
    return m_lastHeartbeat;
}

void PeerModel::setLastHeartbeat(const QTime &lastHeartbeat)
{
    m_lastHeartbeat = lastHeartbeat;
}

const QString PeerModel::toString() const
{
    return "ID: " + m_id +
            " | IP: " + m_address.toString() +
            " | Port: " + QString::number(m_port) +
            " | Last Heartbeat: " + m_lastHeartbeat.toString();
}

bool PeerModel::equals(PeerModel *otherPeerModel)
{
    return m_address == otherPeerModel->address() &&
            m_port == otherPeerModel->port() &&
            m_id == otherPeerModel->id();
}

bool PeerModel::operator ==(const PeerModel &otherPeerModel)
{
    return m_address == otherPeerModel.address() &&
            m_port == otherPeerModel.port() &&
            m_id == otherPeerModel.id();
}

bool PeerModel::operator !=(const PeerModel &otherPeerModel)
{
    return m_address != otherPeerModel.address() ||
            m_port != otherPeerModel.port() ||
            m_id != otherPeerModel.id();
}
