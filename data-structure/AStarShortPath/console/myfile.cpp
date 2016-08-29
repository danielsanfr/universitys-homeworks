#include "myfile.h"

MyFile::MyFile(Graph &myGraph, char *nameFile) {
    int linha = 0;
    string data, dataAux;
    bool status;
    status = readFile(file, nameFile);
    if (!status) {
        cout << "O arquivo não pode ser aberto para leitura.\n";
        cout << "Programa terminando...\n";
        this->status = status;
    } else {
        cout << "Lendo do arquivo" << endl;
        cout << "=====================" << endl;
        getline(file, data);
        while(!file.fail()) {
            addToGraph(myGraph, data, linha);
            getline(file, data);
            ++linha;
        }
        file.close();
    }
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
