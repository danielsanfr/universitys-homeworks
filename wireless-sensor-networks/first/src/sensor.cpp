#include "sensor.hpp"

Sensor::Sensor(QList<float> data, QObject *parent)
    : QObject(parent), id(QUuid::createUuid()), jumps(0), jumpsCount(0), data(data)
{
}

void Sensor::onSenseData()
{
    if (jumpsCount % jumps == 0) {
        Q_EMIT pushData(id.toString(), QVariant(data.at(time % data.size())));
    } else {
        Q_EMIT pushPredictData(id.toString());
    }

    ++time;
    ++jumpsCount;
    Q_EMIT nextSensor();
}

void Sensor::onJumpsToSend(int jumps)
{
    this->jumps = jumps;
}
