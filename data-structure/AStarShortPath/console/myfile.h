#ifndef MYFILE_H
#define MYFILE_H

#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class MyFile {
    public:
        bool status;
        MyFile(Graph &myGraph, char *nameFile);
    protected:
    private:
    ifstream file;
    bool readFile(ifstream &file, char *nameFile);
    void addToGraph(Graph &myGraph, string data, int linha);
};

#endif // MYFILE_H
