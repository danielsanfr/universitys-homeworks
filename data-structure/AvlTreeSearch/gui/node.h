#ifndef NODE_H
#define NODE_H

#include "arraylist.h"
#include <iostream>
#include <string>

using namespace std;

class Node
{
    public:
        ArrayList lines;
        string word;
        Node * right;
        Node * left;
        Node(string palavra, int linha);
        ~Node() {} // Base destructor
        // Return the node’s value
        //int getValue();
        // Set the node’s value
        //void setElement(int it);
        // Return the node’s left child
        //Node * getNodeLeft();
        // Set the node’s left child
        //void setLeft(Node * node);
        // Return the node’s right child
        //Node * getNodeRight();
        // Set the node’s right child
        //void setRight(Node * node);
        // Return true if the node is a leaf, false otherwise
        bool isLeaf();
        bool isFullNode();
};

#endif // NODE_H
