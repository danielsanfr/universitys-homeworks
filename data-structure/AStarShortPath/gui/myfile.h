#ifndef MYFILE_H
#define MYFILE_H

#include <fstream>
#include <string>
#include <cctype>
#include "graph.h"

using namespace std;

class MyFile {
    public:
        bool status;
        MyFile();
        MyFile(Graph &myGraph, char *nameFile);
        bool openFile(Graph &myGraph, char *nameFile);
    protected:
    private:
    ifstream file;

    bool readFile(ifstream &file, char *nameFile);
    void addToGraph(Graph &myGraph, string data, int linha);
};

#endif // MYFILE_H
