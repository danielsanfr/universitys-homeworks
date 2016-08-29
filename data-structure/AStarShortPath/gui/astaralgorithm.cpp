#include "astaralgorithm.h"

AStarAlgorithm::AStarAlgorithm() {
}

bool AStarAlgorithm::search(Graph &myGraph) {
    int custo, i, j;
    bool flag = false, flag2 = false;
    steps = 0;
    Cell *current;
    openList.insert(myGraph.getInit()[0], myGraph.getInit()[1], 0, myGraph.getManhattanHeuristic(myGraph.getInit()[0], myGraph.getInit()[1]));
    while(!flag && !flag2) {
        current = openList.getMin();
        closeList.insert(current);
        for(i = -1; i <= 1; ++i) {
            for(j = -1; j <= 1; ++j) {
                if((i != 0 || j != 0) && !(current->posX == 0 && i == -1) && !(current->posX == 249 && i == 1) && !(current->posY == 0 && j == -1) && !(current->posY == 249 && j == 1)) {
                    if(fabs(i) + fabs(j) == 2)
                        custo = 14 + current->dist;
                    else
                        custo = 10 + current->dist;
                    if(!closeList.search(i + current->posX, j + current->posY) && myGraph.getValue(i + current->posX, j + current->posY) != '#') {
                        if(!openList.search(i + current->posX, j + current->posY)) {
                            Cell *aux = new Cell(i + current->posX, j + current->posY, custo, myGraph.getManhattanHeuristic(i + current->posX, j + current->posY));
                            aux->setDad(current->posX, current->posY);
                            openList.insert(aux);
                            if(myGraph.getEnd()[0] != i + current->posX || myGraph.getEnd()[1] != j + current->posY)
                                myGraph.setValue('O', i + current->posX, j + current->posY);
                        } else {
                            Cell *aux = openList.getCell(i + current->posX, j + current->posY);
                            if(custo < aux->dist) {
                                aux->setDist(custo);
                                aux->setDad(current->posX, current->posY);
                                openList.reorder();
                            }
                        }
                    }
                }
            }
        }
        flag = closeList.search(myGraph.getEnd()[0], myGraph.getEnd()[1]);
        if(openList.length() == 0)
            flag2 = true;
    }
    if(flag) {
        i = myGraph.getEnd()[0];
        j = myGraph.getEnd()[1];
        Cell *aux;
        while(i != myGraph.getInit()[0] || j != myGraph.getInit()[1]) {
            aux = closeList.getCell(i, j);
            i = aux->dadPosX;
            j = aux->dadPosY;
            if(i != myGraph.getInit()[0] || j != myGraph.getInit()[1]) {
                myGraph.setValue('X', i, j);
                ++steps;
            }
        }
    }
    openList.clear();
    closeList.clear();
    return flag;
}

int AStarAlgorithm::getSteps() {
    return steps;
}
