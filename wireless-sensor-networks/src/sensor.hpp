#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <QUuid>
#include <QList>
#include <QObject>
#include <QVariant>

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QList<float> data, QObject *parent = 0);
Q_SIGNALS:
    void nextSensor();
    void pushPredictData(QString id);
    void pushData(QString id, QVariant data);
public Q_SLOTS:
    void onSenseData();
    void onJumpsToSend(int jumps);
private:
    QUuid id;
    int time;
    int jumps;
    int jumpsCount;
    QList<float> data;
};

#endif // SENSOR_HPP
