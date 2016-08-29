#include "node.h"

Node::Node(string palavra, int linha)
{
    word = palavra;
    lines.append(linha);
    right = 0;
    left = 0;
}
/*
int Node::getValue()
{
    return 0;
}

void Node::setElement(int it)
{

}

Node * Node::getNodeLeft()
{
    Node * aux;
    return aux;
}

void Node::setLeft(Node * node)
{

}

Node * Node::getNodeRight()
{
    Node * aux;
    return aux;
}

void Node::setRight(Node * node)
{

}
*/
bool Node::isLeaf()
{
    if(right == 0 && left == 0)
        return true;
    return false;
}

bool Node::isFullNode()
{
    if(right != 0 && left != 0)
        return true;
    return false;
}
