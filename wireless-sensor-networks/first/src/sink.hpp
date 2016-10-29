#ifndef SINK_HPP
#define SINK_HPP

#include <QMap>
#include <QList>
#include <QObject>
#include <QVariant>

class Sink : public QObject
{
    Q_OBJECT
public:
    static Sink* instance(QObject *parent = 0) {
        static Sink *s_instance;
        if (s_instance == 0) {
            s_instance = new Sink(parent);
        }
        return s_instance;
    }
Q_SIGNALS:
    void jumpsToSend(int jumps);
public Q_SLOTS:
    void onPushPredictData(QString id);
    void onPushData(QString id, QVariant data);
private:
    explicit Sink(QObject *parent = 0);
    void computeTime(QString nodeId);
    void saveData();
    int time;
    QString firstNodeId;
    QMap<QString, int> nodesjumps;
    QMap<QString, QList<float> > nodesData;
};

#endif // SINK_HPP
