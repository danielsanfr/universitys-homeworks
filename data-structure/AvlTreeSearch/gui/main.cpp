#include <QApplication>
#include "textfinder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TextFinder w;
    w.show();
    
    return a.exec();
}
