#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "mymatrix.h"
#include "myfile.h"
#include "astaralgorithm.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
    
    public:
        explicit Widget(QWidget *parent = 0);
        ~Widget();

private slots:
    void on_startButton_clicked();

    void on_openButton_clicked();

    void on_genetareButton_clicked();

    void on_aStarButton_clicked();

    void on_dijkstraButton_clicked();

private:
    bool aStar;
    bool dijkstra;
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    MyMatrix *matrix;
    Graph myGraph;
    MyFile file;
    AStarAlgorithm fetchType;
    void loadTextFile(QString fileName);
    void drawMatrix();
};

#endif // WIDGET_H
