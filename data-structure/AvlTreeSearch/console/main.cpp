#include <QCoreApplication>

#include <iostream>

#include "myfile.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string palavra;
    char * nameFile = (char*) malloc(sizeof(char)*100);
    cin >> nameFile;
    cout << "=====================" << endl;
    MyFile texto(nameFile);
    cin >> palavra;
    cout << palavra;
    texto.searchWord(palavra);

    return a.exec();
}
