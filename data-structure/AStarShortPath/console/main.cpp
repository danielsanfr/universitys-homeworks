#include <iostream>

#include "myfile.h"
#include "graph.h"
#include "astaralgorithm.h"

using namespace std;

int main(int argc, char *argv[])
{
    int i, j;
    Graph myGraph;
    char * nameFile = (char*) malloc(sizeof(char)*100);
    cin >> nameFile;
    cout << "=====================" << endl;
    MyFile labirinto(myGraph, nameFile);
    if(!labirinto.status)
        return 0;
    AStarAlgorithm fetchType;
    bool flag = !fetchType.search(myGraph);

    for(i = 0; i < 250; ++i) {
        for(j = 0; j < 250; ++j)
            cout << myGraph.getValue(i, j);
        cout << endl;
    }
    if(flag) {
        cout << "===============================================" << endl;
        cout << "Nao foi possivel achar um caminho!" << endl;
        cout << "===============================================" << endl;
    } else {
        cout << "===============================================" << endl;
        cout << "Foram dados " << fetchType.getSteps() << " passos do inicio ate o final." << endl;
        cout << "===============================================" << endl;
    }
    return 0;
}
