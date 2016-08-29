#ifndef CELL_H
#define CELL_H

using namespace std;

class Cell {
    public:
        int posX;
        int posY;
        int dadPosX;
        int dadPosY;
        int dist;
        int heuristic;
        int aprox;
        Cell * next;
        Cell(Cell *cell);
        Cell(int valueX, int valueY, int distance, int heurist);
        ~Cell();
        void setDad(int valueX, int valueY);
        void setDist(int distance);
};

#endif // CELL_H
