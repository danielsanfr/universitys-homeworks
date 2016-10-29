#include "simulator.hpp"

#include <QList>
#include <QFile>

Simulator::Simulator(int argc, char *argv[]) : QCoreApplication(argc, argv),
    environment(new Environment()) { }

Simulator::~Simulator()
{
    environment->deleteLater();
}

int Simulator::execute()
{
    QFile file(":/data/annual.csv");
    if (!file.open(QFile::ReadOnly | QFile::Text)) return -1;

    QList<float> data;
    while (!file.atEnd())
        data.append(file.readLine().replace("\n", "").toFloat());

    environment->configureSink(this);
    environment->configureSensors(10, data);
    environment->run();
    return exec();
}
