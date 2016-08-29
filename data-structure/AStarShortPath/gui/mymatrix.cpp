#include "mymatrix.h"

MyMatrix::MyMatrix(int i, int j, char cell) {
    this->i = j;
    this->j = i;
    this->cell = cell;
}

QRectF MyMatrix::boundingRect() const {
    int size = 4;
    return QRectF(i*size, j*size, size, size);
}

void MyMatrix::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rec = boundingRect();
    if(cell == ' ')
        painter->fillRect(rec, QBrush(Qt::darkGreen));
    else if(cell == '#')
        painter->fillRect(rec, QBrush(Qt::gray));
    else if(cell == 'X')
        painter->fillRect(rec, QBrush(Qt::blue));
    else if(cell == 'O')
        painter->fillRect(rec, QBrush(Qt::cyan));
    else if(cell == 'I')
        painter->fillRect(rec, QBrush(Qt::yellow));
    else if(cell == 'F')
        painter->fillRect(rec, QBrush(Qt::red));
    painter->drawRect(rec);
}
