#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include "myfile.h"
#include <QWidget>
#include <QtGui>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

namespace Ui {
class TextFinder;
}

class TextFinder : public QWidget
{
    Q_OBJECT
    
public:
    explicit TextFinder(QWidget *parent = 0);
    ~TextFinder();
    
private slots:
    void on_openButton_clicked();


    void on_findButton_clicked();


private:
    MyFile file;
    QString word;
    Ui::TextFinder *ui;
    void loadTextFile(QString);
};

#endif // TEXTFINDER_H
