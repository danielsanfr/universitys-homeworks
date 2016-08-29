#ifndef MYAVLTREE_H
#define MYAVLTREE_H

#include "node.h"
#include <iostream>
#include <climits>
#include <cstdlib>
#include <sstream>

using namespace std;

class MyAvlTree
{
    public:
        string fraseSaida;
        MyAvlTree();
        void clear();
		void insert(string palavra, int linha);
		int height();
		void pathForNode(string palavra);
		bool isFull();
		bool isComplete();
    protected:
    private:
        Node * root;
        ArrayList lines;
        int quantidade;
        int quantidadeAux;
        int alturaAux;
        int tamLista;
        int alt;
        int altMax;
        int pos;
        int aux;
        bool full;
        bool auxFull;
        bool complete;
        bool auxComplete;
        int * lista;
        void auxHeight(Node * current);
        void listar(int item);
        void auxIsFull(Node * current);
        void auxIsComplete(Node * current);
        int getFactor(Node * current);
        void balance(Node * current);
        void balanceRoot();
        void rotateLeft(Node * node, Node * child, int direcao);
        void rotateRight(Node * node, Node * child, int direcao);
        //void rotateTwice(Node * node, Node * child);
        //void rotateOnce (Node * node, Node * child);
};

#endif // MYAVLTREE_H
