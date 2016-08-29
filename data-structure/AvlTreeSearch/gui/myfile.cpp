#include "myfile.h"

MyFile::MyFile()
{

}

bool MyFile::openFile(char * nameFile)
{
    int linha = 0;
    string data, dataAux;
    bool status = readFile(file, nameFile);
    if (!status)
        return status;
    else
    {
        words.clear();
        //cout << "Lendo do arquivo" << endl;
        //cout << "=====================" << endl;
        getline(file, data);
        while(!file.fail())
        {
            addTheTree(data, linha);
            getline(file, data);
            ++linha;
        }
        file.close();
    }
    return status;
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
    string palavraAux;
    for(size_t i = 0; i < palavra.length(); ++i)
        palavraAux += tolower(palavra.at(i));
    words.pathForNode(palavraAux);
    fraseSaida = words.fraseSaida;
}




















