#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

class MyMatrix : public QGraphicsItem {
public:
    MyMatrix(int i, int j, char cell);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int i;
    int j;
    char cell;
};

#endif // MYMATRIX_H
