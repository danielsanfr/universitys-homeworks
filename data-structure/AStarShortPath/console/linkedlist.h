#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "cell.h"

class LinkedList {
    public:
        LinkedList();
        ~LinkedList(); // Base destructor
        void clear();
        void insert(Cell *cell);
        void insert(int valueX, int valueY, int dist, int heuristic);
        int remove();
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        int length();
        int currPos();
        void moveToPos(int pos);
        int getValue();
        bool search(int valueX, int valueY);
        void reorder();
        Cell *getMin();
        Cell *getCell(int valueX, int valueY);
    protected:
    private:
        Cell * head;
        int sizeList;
        int curr;
};

#endif // LINKEDLIST_H
