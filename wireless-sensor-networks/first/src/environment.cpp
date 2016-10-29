#include "environment.hpp"

#include <QThread>

Environment::Environment(QObject *parent) : QObject(parent)
{
}

Environment::~Environment()
{
    Sink::instance()->deleteLater();
    foreach (Sensor *node, nodes) {
        node->deleteLater();
    }
}

void Environment::run()
{
    Q_EMIT Sink::instance()->jumpsToSend(4);
    Q_EMIT startSensors();
}

void Environment::configureSink(QObject *parent)
{
    Sink::instance(parent);
}

void Environment::configureSensors(int quantity, QList<float> data)
{
    Sensor *sensorTmp;
    Sink *sink = Sink::instance();
    Sensor *sensor = new Sensor(data);
    QThread *thread = new QThread();
    sensor->moveToThread(thread);
    moveToThread(thread);
    nodes.append(sensor);
    connectSensorToSink(sensor, sink);
    for (int i = 1; i < quantity; ++i) {
        sensorTmp = new Sensor(data);
        sensorTmp->moveToThread(thread);
        nodes.append(sensorTmp);

        connectSensorToSink(sensorTmp, sink);
        connect(sensor, &Sensor::nextSensor, sensorTmp, &Sensor::onSenseData, Qt::QueuedConnection);
        sensor = sensorTmp;
    }
    sensor = nodes.at(0);
    connect(sensorTmp, &Sensor::nextSensor, sensor, &Sensor::onSenseData, Qt::QueuedConnection);
    connect(this, &Environment::startSensors, sensor, &Sensor::onSenseData, Qt::QueuedConnection);

    thread->start();
}

void Environment::connectSensorToSink(Sensor *sensor, Sink *sink)
{
    connect(sensor, &Sensor::pushPredictData, sink, &Sink::onPushPredictData, Qt::QueuedConnection);
    connect(sink, &Sink::jumpsToSend, sensor, &Sensor::onJumpsToSend, Qt::QueuedConnection);
    connect(sensor, &Sensor::pushData, sink, &Sink::onPushData, Qt::QueuedConnection);
}
