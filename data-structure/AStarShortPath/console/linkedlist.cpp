#include "linkedlist.h"

LinkedList::LinkedList() {
    sizeList = 0;
    curr = 0;
    head = 0;
}

LinkedList::~LinkedList() {
    if(head != 0)
        delete head;
}

Cell *LinkedList::getMin() {
    --sizeList;
    Cell *aux = head;
    head = head->next;
    return aux;
}

Cell *LinkedList::getCell(int valueX, int valueY) {
    Cell *current = head;
    while(current != 0) {
        if(current->posX == valueX && current->posY == valueY)
            return current;
        else
            current = current->next;
    }
    return current;
}

bool LinkedList::search(int valueX, int valueY) {
    bool flag = false;
    Cell *current = head;
    while(current != 0 && !flag) {
        if(current->posX == valueX && current->posY == valueY)
            flag = true;
        current = current->next;
    }
    return flag;
}

void LinkedList::reorder() {
    int i = -1, j = 0;
    bool flag = true;
    Cell *current = head;
    Cell *aux = 0;
    while(flag) {
        while(current != 0) {
            if(current->next != 0) {
                if(current->aprox > current->next->aprox) {
                    aux = current;
                    break;
                }
            }
            current = current->next;
        }
        if(aux != 0) {
            if(aux->posX == head->posX && aux->posY == head->posY) {
                current = aux->next;
                aux->next = current->next;
                current->next = aux;
                head = current;
                current = head;
                aux = 0;
            } else {
                current = head;
                while(current != 0) {
                    if(current->next != 0) {
                        if(current->next->posX == aux->posX && current->next->posY == aux->posY) {
                            current->next = aux->next;
                            break;
                        }
                    }
                    current = current->next;
                }
                aux->next = 0;
                current = head;
                for(j = 0; current != 0; ++j) {
                    if(aux->aprox < current->aprox) {
                        current = 0;
                        break;
                    }
                    else {
                        current = current->next;
                    }
                }
                if(j == 0) {
                    Cell * cell = head;
                    head = aux;
                    head->next = cell;
                } else {
                    current = head;
                    for(i = 0; i < j - 1; ++i)
                        current = current->next;
                    aux->next = current->next;
                    current->next = aux;
                }
                current = head;
                aux = 0;
            }
        } else
            flag = false;
    }
}

void LinkedList::clear() {
    curr = 0;
    if(head != 0)
        delete head;
    head = 0;
    sizeList = 0;
}

void LinkedList::insert(Cell *cell) {
    int i = -1, j = 0;
    ++sizeList;
    Cell *newCell = new Cell(cell);
    Cell *current = head;
    for(curr = 0; current != 0; ++curr) {
        if(newCell->aprox <= current->aprox) {
            current = 0;
            j = curr;
        }
        else
            current = current->next;
    }
    if(curr > j + 1)
        j = curr;
    if(head == 0)
        head = newCell;
    else if(j == 0) {
        Cell * aux = head;
        head = newCell;
        head->next = aux;
    } else {
        current = head;
        for(i = 0; i < j - 1; ++i)
            current = current->next;
        newCell->next = current->next;
        current->next = newCell;
    }
}

void LinkedList::insert(int valueX, int valueY, int dist, int heuristic) {
    int i = -1, j = 0;
    ++sizeList;
    Cell * newCell = new Cell(valueX, valueY, dist, heuristic);
    Cell *current = head;
    for(curr = 0; current != 0; ++curr) {
        if(newCell->aprox <= current->aprox) {
            current = 0;
            j = curr;
        }
        else
            current = current->next;
    }
    if(curr > j + 1)
        j = curr;
    if(head == 0)
        head = newCell;
    else if(j == 0) {
        Cell * aux = head;
        head = newCell;
        head->next = aux;
    } else {
        current = head;
        for(i = 0; i < j - 1; ++i)
            current = current->next;
        newCell->next = current->next;
        current->next = newCell;
    }
}

int LinkedList::remove() {
    int i;
    int value;
    if(sizeList == 0)
        return 0;
    else
    {
        --sizeList;
        Cell * current = head;
        Cell * aux;
        if(curr == 0)
        {
            value = head->posX;
            head = head->next;
            delete current;
        }
        else
        {
            for(i = 0 ; i < curr - 1 ; ++i)
                current = current->next;
            aux = current->next;
            current->next = aux->next;
            value = aux->posX;
            delete aux;
        }
        return value;
    }
}

void LinkedList::moveToStart() {
    curr = 0;
}

void LinkedList::moveToEnd() {
    curr = sizeList - 1;
}

void LinkedList::prev() {
    if(curr > 0) --curr;
}

void LinkedList::next() {
    if(curr < sizeList - 1)
        ++curr;
}

int LinkedList::length() {
    return sizeList;
}

int LinkedList::currPos() {
    return curr;
}

void LinkedList::moveToPos(int pos) {
    if(pos > sizeList - 1)
        curr = sizeList - 1;
    else if(pos < 0)
        curr = 0;
    else
        curr = pos;
}

int LinkedList::getValue() {
    int i;
    Cell * current = head;
    if(head == 0)
        return 0;
    for(i = 0 ; i < curr ; ++i)
        current = current->next;
    return current->posX;
}
