#include <QCoreApplication>

#include "maintestthread.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    new MainTestThread();
    return a.exec();
}
