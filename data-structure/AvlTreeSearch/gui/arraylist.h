#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <stdlib.h>

using namespace std;

class ArrayList
{
    public:
        ArrayList();
        void clear();
        void insert(int item);
        void append(int item);
        int remove();
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        int length();
        int currPos();
        void moveToPos(int pos);
        int getValue();
    protected:
    private:
        int *lista;
        int curr;
        int sizeList;
};

#endif // ARRAYLIST_H
