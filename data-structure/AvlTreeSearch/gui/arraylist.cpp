#include "arraylist.h"

ArrayList::ArrayList()
{
    curr = 0;
    sizeList = 0;
}

void ArrayList::clear()
{
    if(sizeList != 0)
    {
        free(lista);
        lista = NULL;
        curr = 0;
        sizeList = 0;
    }
}

void ArrayList::insert(int item)
{
    int i;
    ++sizeList;
    if(sizeList == 1)
        lista = (int*) malloc(sizeof(int));
    else
    {
        lista = (int*) realloc(lista, sizeof(int)*sizeList);
        for(i = sizeList - 2 ; i >= curr ; --i)
            lista[i + 1] = lista[i];
    }
    lista[curr] = item;
}

void ArrayList::append(int item)
{
    ++sizeList;
    if(sizeList == 1)
        lista = (int*) malloc(sizeof(int));
    else
        lista = (int*) realloc(lista, sizeof(int)*sizeList);
    lista[sizeList - 1] = item;
}

int ArrayList::remove()
{
    int i, element;
    if(sizeList == 0)
		return 0;
    else
    {
        element = lista[curr];
        for(i = curr ; i < sizeList - 1; ++i)
            lista[i] = lista[i + 1];
        --sizeList;
        if(curr == sizeList)
            --curr;
        lista = (int*) realloc(lista, sizeof(int)*sizeList);
        return element;
    }
}

void ArrayList::moveToStart()
{
    curr = 0;
}

void ArrayList::moveToEnd()
{
    curr = sizeList - 1;
}

void ArrayList::prev()
{
    if(curr > 0)
        --curr;
}

void ArrayList::next()
{
    if(curr < sizeList - 1)
        ++curr;
}

int ArrayList::length()
{
    return sizeList;
}

int ArrayList::currPos()
{
    return curr;
}

void ArrayList::moveToPos(int pos)
{
    if(pos > sizeList - 1)
        curr = sizeList - 1;
    else if(pos < 0)
        curr = 0;
    else
        curr = pos;
}

int ArrayList::getValue()
{
    if(sizeList == 0)
        return 0;
    return lista[curr];
}
