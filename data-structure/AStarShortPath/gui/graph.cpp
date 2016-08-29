#include "graph.h"

Graph::Graph() {
    int i, j;
    for(i = 0; i < 250; ++i)
        for(j = 0; j < 250; ++j)
            matriz[i][j] = ' ';
}

void Graph::addVvertex(char data, int i, int j) {
    matriz[i][j] = data;
}

void Graph::clear() {
    int i, j;
    for(i = 0; i < 250; ++i)
        for(j = 0; j < 250; ++j)
            matriz[i][j] = ' ';
}

char Graph::getValue(int i, int j) {
    return matriz[i][j];
}

void Graph::setValue(char data, int i, int j) {
    matriz[i][j] = data;
}

int Graph::getManhattanHeuristic(int i, int j) {
    return 10*(fabs(xFim - i) + fabs(yFim - j));
}

void Graph::setInit(int i, int j) {
    xInicio = i;
    yInicio = j;
}

void Graph::setEnd(int i, int j) {
    xFim = i;
    yFim = j;
}

int *Graph::getInit() {
    int *pos = new int[2];
    pos[0] = xInicio;
    pos[1] = yInicio;
    return pos;
}

int *Graph::getEnd() {
    int *pos = new int[2];
    pos[0] = xFim;
    pos[1] = yFim;
    return pos;
}
