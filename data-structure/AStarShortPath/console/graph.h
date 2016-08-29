#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

class Graph {
    public:
        Graph();
        void addVvertex(char data, int i, int j);
        char getValue(int i, int j);
        void setValue(char data, int i, int j);
        void setInit(int i, int j);
        void setEnd(int i, int j);
        int *getInit();
        int *getEnd();
        int getManhattanHeuristic(int i, int j);
    protected:
    private:
        int xInicio;
        int yInicio;
        int xFim;
        int yFim;
        char matriz[250][250];
};

#endif // GRAPH_H
