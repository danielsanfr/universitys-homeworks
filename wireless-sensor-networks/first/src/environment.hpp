#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <QList>
#include <QObject>

#include "sink.hpp"
#include "sensor.hpp"

class Environment : public QObject
{
    Q_OBJECT
public:
    explicit Environment(QObject *parent = 0);
    ~Environment();
    void run();
    void configureSink(QObject *parent = 0);
    void configureSensors(int quantity, QList<float> data);
Q_SIGNALS:
    void startSensors();
private:
    void connectSensorToSink(Sensor *sensor, Sink *sink);
    QList<Sensor *> nodes;
};

#endif // ENVIRONMENT_HPP
