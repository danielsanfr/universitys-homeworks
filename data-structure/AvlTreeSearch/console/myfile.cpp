#include "myfile.h"

MyFile::MyFile(char * nameFile)
{
    int linha = 0;
    string data, dataAux;
    bool status;
    status = readFile(file, nameFile);
    if (!status)
    {
        cout << "O arquivo não pode ser aberto para leitura.\n";
        cout << "Programa terminando...\n";
    }
    else
    {
        cout << "Lendo do arquivo" << endl;
        cout << "=====================" << endl;
        getline(file, data);
        while(!file.fail())
        {
            addTheTree(data, linha);
            getline(file, data);
            ++linha;
        }
        file.close();
    }
}

bool MyFile::readFile(ifstream & file, char * nameFile)
{
    file.open(nameFile);
    return !(file.fail()||!file.is_open()||!file.good());
}

void MyFile::addTheTree(string data, int linha)
{
    string palavra;
    for(size_t i = 0; i < data.length(); ++i)
    {
        if(data.at(i) != ' ')
            palavra += tolower(data.at(i));
        else
        {
            words.insert(palavra, linha);
            //cout << palavra << endl;
            palavra.clear();
        }
    }
    words.insert(palavra, linha);
    //cout << palavra << endl;
    palavra.clear();
}

void MyFile::searchWord(string palavra)
{
    words.pathForNode(palavra);
}




















