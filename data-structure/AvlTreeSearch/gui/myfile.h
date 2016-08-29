#ifndef MYFILE_H
#define MYFILE_H

#include "myavltree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class MyFile
{
    public:
        string fraseSaida;
        MyFile();
        bool openFile(char * nameFile);
        void searchWord(string palavra);
    protected:
    private:
    ifstream file;
    MyAvlTree words;
    void addTheTree(string data, int linha);
    bool readFile(ifstream & file, char * nameFile);
};

#endif // MYFILE_H
