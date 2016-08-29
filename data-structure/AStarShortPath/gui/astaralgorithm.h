#ifndef ASTAR_H
#define ASTAR_H

#include <QDebug>
#include <cmath>
#include "graph.h"
#include "cell.h"
#include "linkedlist.h"

class AStarAlgorithm {
    public:
        AStarAlgorithm();
        bool search(Graph &myGraph);
        int getSteps();
    protected:
    private:
        int steps;
        LinkedList openList;
        LinkedList closeList;
};

#endif // ASTAR_H
