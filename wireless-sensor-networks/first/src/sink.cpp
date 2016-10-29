#include "sink.hpp"

#include <QFile>
#include <QTime>
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>

float randFloat(float a, float b)
{
    bool flag = true;
    float min, max, rand;
    if (a > b) {
        max = a;
        min = b;
    } else {
        max = b;
        min = a;
    }
    do {
        int teste = qrand();
        rand = (teste % 100000) / 100000.0;
        if (rand >= min && rand <= max) {
            flag = false;
        } else {
            rand = -1*rand;
            if (rand >= min && rand <= max)
                flag = false;
        }
    } while (flag);
//    qDebug() << rand;
    return rand;
}

Sink::Sink(QObject *parent) : QObject(parent)
{
    qsrand(QTime::currentTime().msec());
}

void Sink::computeTime(QString nodeId)
{
    if (firstNodeId.isEmpty())
        firstNodeId = nodeId;
    else if (firstNodeId == nodeId)
        ++time;
    else
        return;

//    qDebug() << time;
    if (time == 272) {
        time = 0;
        saveData();
        QCoreApplication::instance()->exit();
    }
}

void Sink::saveData()
{
    QFile file("sensor_predicted_data.csv");
    if (!file.open(QFile::WriteOnly | QFile::Text)) return;

    QTextStream out(&file);
    QList<float> dataToSave = nodesData.values().at(1);
    for (int i = 0; i < dataToSave.size(); ++i) {
        out << i << "," << dataToSave.at(i) << "\n";
    }
}

void Sink::onPushPredictData(QString id)
{
    nodesjumps.insert(id, nodesjumps.value(id) + 1);
    computeTime(id);
}

void Sink::onPushData(QString id, QVariant data)
{
//    qDebug() << "data1";
    float newData = data.toFloat();
    QList<float> nodeData = nodesData.value(id);
    if (!nodeData.isEmpty()) {
        float lastData = nodeData.last();
        int size = nodesjumps.value(id);
        for (int i = 0; i < size; ++i) {
            nodeData.append(randFloat(newData, lastData));
        }
    }
//    qDebug() << "data2";

    nodesjumps.insert(id, 0);
    nodeData.append(newData);
    nodesData.insert(id, nodeData);
    computeTime(id);
}
