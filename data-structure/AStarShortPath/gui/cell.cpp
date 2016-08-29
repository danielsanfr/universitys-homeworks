#include "cell.h"

Cell::Cell(Cell *cell) {
    posX = cell->posX;
    posY = cell->posY;
    dadPosX = cell->dadPosX;
    dadPosY = cell->dadPosY;
    dist = cell->dist;
    heuristic = cell->heuristic;
    aprox = cell->dist + cell->heuristic;
    next = 0;
}

Cell::Cell(int valueX, int valueY, int distance, int heurist) {
    posX = valueX;
    posY = valueY;
    dadPosX = -1;
    dadPosY = -1;
    dist = distance;
    heuristic = heurist;
    aprox = dist + heuristic;
    next = 0;
}

Cell::~Cell() {
    delete next;
}

void Cell::setDad(int valueX, int valueY) {
    dadPosX = valueX;
    dadPosY = valueY;
}

void Cell::setDist(int distance) {
    dist = distance;
    aprox = dist + heuristic;
}
