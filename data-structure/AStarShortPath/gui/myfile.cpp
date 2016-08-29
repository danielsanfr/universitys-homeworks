#include "myfile.h"

MyFile::MyFile() {

}

MyFile::MyFile(Graph &myGraph, char *nameFile) {
    int linha = 0;
    string data;
    bool status;
    status = readFile(file, nameFile);
    if (!status)
        this->status = status;
    else {
        getline(file, data);
        while(!file.fail()) {
            addToGraph(myGraph, data, linha);
            getline(file, data);
            ++linha;
        }
        file.close();
    }
}

bool MyFile::openFile(Graph &myGraph, char *nameFile) {
    int linha = 0;
    string data;
    bool status;
    status = readFile(file, nameFile);
    if (!status) {
        this->status = status;
    } else {
        getline(file, data);
        while(!file.fail()) {
            addToGraph(myGraph, data, linha);
            getline(file, data);
            ++linha;
        }
        file.close();
    }
    return status;
}

bool MyFile::readFile(ifstream &file, char *nameFile) {
    file.open(nameFile);
    return !(file.fail()||!file.is_open()||!file.good());
}

void MyFile::addToGraph(Graph &myGraph, string data, int linha) {
    for(size_t i = 0; i < data.length(); ++i) {
        myGraph.addVvertex(data.at(i), linha, i);
        if(data.at(i) == 'I')
            myGraph.setInit(linha, i);
        else if(data.at(i) == 'F')
            myGraph.setEnd(linha, i);
    }
}
