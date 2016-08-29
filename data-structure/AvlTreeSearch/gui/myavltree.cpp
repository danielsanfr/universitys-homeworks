#include "myavltree.h"

MyAvlTree::MyAvlTree()
{
    quantidade = 0;
    quantidadeAux = 0;
    lista = 0;
    tamLista = 0;
    root = 0;
    alturaAux = 0;
    alt = 0;
    full = true;
    complete = true;
    auxFull = true;
    auxComplete = true;
}

void MyAvlTree::clear()
{
    Node * current;
    Node * aux;
    if(root != 0)
    {
        while(!root->isLeaf())
        {
            current = root;
            while(!current->isLeaf())
            {
                if(current->left != 0)
                {
                    if(current->left->isLeaf())
                    {
                        aux = current;
                        current = current->left;
                        delete current;
                        aux->left = 0;
                        current = aux;
                    }
                    else
                        current = current->left;
                }
                else if(current->right != 0)
                {
                    if(current->right->isLeaf())
                    {
                        aux = current;
                        current = current->right;
                        delete current;
                        aux->right = 0;
                        current = aux;
                    }
                    else
                        current = current->right;
                }
            }
        }
    }
    delete root;
    quantidade = 0;
    quantidadeAux = 0;
    lista = 0;
    tamLista = 0;
    root = 0;
    alturaAux = 0;
    alt = 0;
    full = true;
    complete = true;
    auxFull = true;
    auxComplete = true;
}

void MyAvlTree::insert(string palavra, int linha)
{
    bool aux = true;
    bool flag = false;
    Node * newNode = new Node(palavra, linha);
    auxFull = true;
    auxComplete = true;
    ++quantidade;
    if(root ==  0)
    {
        root = newNode;
        alt = 1;
    }
    else
    {
        Node * current = root;
        while(!current->isLeaf() || aux)
        {
            if(palavra.compare(current->word) == 0)
            {
                current->lines.append(linha);
                aux = false;
                flag = true;
                current = new Node(palavra, INT_MIN);
            }
            else if(palavra.compare(current->word) < 0)
            {
                if(current->left == 0)
                {
                    current->left = newNode;
                    current = newNode;
                    aux = false;
                }
                else
                    current = current->left;
            }
            else
            {
                if(current->right == 0)
                {
                    current->right = newNode;
                    current = newNode;
                    aux = false;
                }
                else
                    current = current->right;
            }
        }
        cout << endl;
        if(flag)
            delete current;
    }
    this->aux = 0;
    balance(root);
}

int MyAvlTree::height()
{
    altMax = INT_MIN;
    if(quantidade != quantidadeAux)
    {
        quantidadeAux = quantidade;
        auxHeight(root);
        alt = altMax;
    }
    return alt;
}

void MyAvlTree::auxHeight(Node * current)
{
    ++alturaAux;
    if(current->left != 0)
        auxHeight(current->left);
    if(current->right != 0)
        auxHeight(current->right);
    if(current->isLeaf())
        if(altMax < alturaAux)
            altMax = alturaAux;
    --alturaAux;
}

void MyAvlTree::pathForNode(string palavra)
{
    int tamCam = 0;
    bool flag = true;
    bool noFile = false;
    Node * current = root;
    if(root == 0)
    {
        flag = false;
        noFile = true;
    }
    else
    {
        while(palavra.compare(current->word) != 0 && flag)
        {
            if(palavra.compare(current->word) < 0)
            {
                if(current->left == 0)
                    flag = false;
                else
                    current = current->left;
            }
            else
            {
                if(current->right == 0)
                    flag = false;
                else
                    current = current->right;
            }
            ++tamCam;
        }
    }
    fraseSaida.clear();
    if(flag)
    {
        int i;
        stringstream buffer;
        fraseSaida = "A palavra '" + current->word + "' se encontra nas linhas: ";
        for(i = 0, current->lines.moveToStart(); i < current->lines.length(); ++i, current->lines.next())
        {
            if(i == 0)
            {
                if(current->lines.length() - 1 == 0)
                {
                    fraseSaida.clear();
                    fraseSaida = "A palavra '" + current->word + "' se encontra na linha: ";
                    buffer << current->lines.getValue() << ".";
                }
                else
                    buffer << current->lines.getValue();
            }
            else if(i == current->lines.length() - 1)
                buffer << " e " << current->lines.getValue() << ".";
            else
                buffer << ", " << current->lines.getValue();
        }
        fraseSaida += buffer.str();
    }
    else
    {
        if(noFile)
            fraseSaida = "Nenhum arquivo foi carregado ainda!";
        else
            fraseSaida = "A palavra pesquisada nao foi localizada!";
    }
}

bool MyAvlTree::isFull()
{
    if(auxFull)
    {
        if(root == 0)
            return full;
        auxIsFull(root);
        auxFull = false;
    }
    return full;
}

void MyAvlTree::auxIsFull(Node * current)
{
    if(current->left != 0)
        auxIsFull(current->left);
    if(current->right != 0)
        auxIsFull(current->right);
    if(!(current->isLeaf() || current->isFullNode()))
        full = false;
}

bool MyAvlTree::isComplete()
{
    if(auxComplete)
    {
        if(root == 0)
            return complete;
        auxComplete = false;
        int i, aux = -1;
        bool flag = false;
        tamLista = 0;
        lista = new int[quantidade];
        pos = 1;
        aux = 1;
        auxIsComplete(root);
        for(i = 0; i < tamLista; ++i)
        {
            if(lista[i] == INT_MAX || lista[i] == 0)
            {
                flag = true;
                aux = i;
            }
            if(aux != i && flag && lista[i] != INT_MAX)
                complete = false;
        }
        delete [] lista;
        lista = 0;
        tamLista = 0;
        return complete;
    }
    else
        return complete;
}

void MyAvlTree::auxIsComplete(Node * current)
{
    if(current->word.empty())
        listar(INT_MIN);
    else
        listar(1);
    pos *= 2;
    if(!current->isLeaf())
    {
        if(current->left != 0)
            auxIsComplete(current->left);
        else
            listar(INT_MAX);
        ++pos;
        if(current->right != 0)
            auxIsComplete(current->right);
        else
            listar(INT_MAX);
    }
    else
        ++pos;
    pos = (pos - 1)/2;
}

void MyAvlTree::listar(int item)
{
    if(pos > quantidade)
        lista = (int*) realloc(lista, sizeof(int)*pos);
    if(pos > tamLista)
        tamLista = pos;
    lista[pos - 1] = item;
}

int MyAvlTree::getFactor(Node * current)
{
    int altLeft, altHight;
    if(current->left != 0)
    {
        altMax = INT_MIN;
        auxHeight(current->left);
        altLeft = altMax;
    }
    else
        altLeft = 0;
    if(current->right != 0)
    {
        altMax = INT_MIN;
        auxHeight(current->right);
        altHight = altMax;
    }
    else
        altHight = 0;
    return altLeft - altHight;
}

void MyAvlTree::balance(Node * current)
{
    ++this->aux;
    if(!current->isLeaf())
    {
        if(current->left != 0 && !current->left->isLeaf())
        {
            balance(current->left);
            int i = getFactor(current->left);
            int lado = 1;
            if(i < -1)
                rotateLeft(current, current->left, lado);
            else if(i > 1)
                rotateRight(current, current->left, lado);
        }
        if(current->right != 0 && !current->right->isLeaf())
        {
            balance(current->right);
            int i = getFactor(current->right);
            int lado = 2;
            if(i < -1)
                rotateLeft(current, current->right, lado);
            else if(i > 1)
                rotateRight(current, current->right, lado);
        }
    }
    --this->aux;
    if(this->aux == 0)
        balanceRoot();
}

void MyAvlTree::balanceRoot()
{
    int i = getFactor(root);
    if(i < -1)
    {
        if(getFactor(root->right) <= 0)
        {
            Node * child = root;
            root = root->right;
            child->right = root->left;
            root->left = child;
        }
        else
        {
            Node * child = root;
            Node * childAux = root->right;
            root = childAux->left;
            child->right = root->left;
            childAux->left = root->right;
            root->right = childAux;
            root->left = child;
        }
    }
    else if(i > 1)
    {
        if(getFactor(root->left) >= 0)
        {
            Node * child = root;
            root = root->left;
            child->left = root->right;
            root->right = child;
        }
        else
        {
            Node * child = root;
            Node * childAux = root->left;
            root = childAux->right;
            child->left = root->right;
            childAux->right = root->left;
            root->right = child;
            root->left = childAux;
        }
    }
}

void MyAvlTree::rotateLeft(Node * node, Node * child, int lado)
{
    if(lado == 2)
    {
        if(getFactor(child->right) <= 0)
        {
            node->right = child->right;
            child->right = node->right->left;
            node->right->left = child;
        }
        else
        {
            Node * aux = child->right;
            node->right = aux->left;
            child->right = node->right->left;
            aux->left = node->right->right;
            node->right->left = child;
            node->right->right = aux;
        }
    }
    else
    {
        if(getFactor(child->right) <= 0)
        {
            node->left = child->right;
            child->right = node->left->left;
            node->left->left = child;
        }
        else
        {
            Node * aux = child->right;
            node->left = aux->left;
            child->right = node->left->left;
            aux->left = node->left->right;
            node->left->left = child;
            node->left->right = aux;
        }
    }
}

void MyAvlTree::rotateRight(Node * node, Node * child, int lado)
{
    if(lado == 2)
    {
        if(getFactor(child->left) >= 0)
        {
            node->right = child->left;
            child->left = node->right->right;
            node->right->right = child;
        }
        else
        {
            Node * aux = child->left;
            node->right = aux->right;
            child->left = node->right->right;
            aux->right = node->right->left;
            node->right->left = aux;
            node->right->right = child;
        }
    }
    else
    {
        if(getFactor(child->left) >= 0)
        {
            node->left = child->left;
            child->left = node->left->right;
            node->left->right = child;
        }
        else
        {
            Node * aux = child->left;
            node->left = aux->right;
            child->left = node->left->right;
            aux->right = node->left->left;
            node->left->left = aux;
            node->left->right = child;
        }
    }
}

















