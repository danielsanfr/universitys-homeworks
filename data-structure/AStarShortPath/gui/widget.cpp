#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>

typedef QStringList (*_qt_filedialog_open_filenames_hook)(QWidget * parent, const QString &caption, const QString &dir,
                                                          const QString &filter, QString *selectedFilter, QFileDialog::Options options);
typedef QString (*_qt_filedialog_open_filename_hook)     (QWidget * parent, const QString &caption, const QString &dir,
                                                          const QString &filter, QString *selectedFilter, QFileDialog::Options options);
typedef QString (*_qt_filedialog_save_filename_hook)     (QWidget * parent, const QString &caption, const QString &dir,
                                                          const QString &filter, QString *selectedFilter, QFileDialog::Options options);
typedef QString (*_qt_filedialog_existing_directory_hook)(QWidget *parent, const QString &caption, const QString &dir,
                                                          QFileDialog::Options options);

extern Q_GUI_EXPORT _qt_filedialog_open_filename_hook qt_filedialog_open_filename_hook;
extern Q_GUI_EXPORT _qt_filedialog_open_filenames_hook qt_filedialog_open_filenames_hook;
extern Q_GUI_EXPORT _qt_filedialog_save_filename_hook qt_filedialog_save_filename_hook;
extern Q_GUI_EXPORT _qt_filedialog_existing_directory_hook qt_filedialog_existing_directory_hook;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget) {
    ui->setupUi(this);
    aStar = true;
    dijkstra = false;

    ui->dijkstraButton->setEnabled(false);
    ui->startButton->setEnabled(false);

    ui->lcdNumber->setMode(QLCDNumber::Dec);
//    ui->lcdNumber->setNumDigits(5);
//    ui->lcdNumber->setDigitCount(5);

    scene = new QGraphicsScene(this);
    //ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene(scene);

//    QBrush redBrush(Qt::red);
//    QPen blackpan(Qt::black);

//    blackpan.setWidth(1);

//    rectangle = scene->addRect(10, 10, 100, 100, blackpan, redBrush);
//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
}

Widget::~Widget() {
    delete ui;
}

void Widget::loadTextFile(QString fileName) {
    QByteArray ba = fileName.toLocal8Bit();
    char *name = ba.data();
    if(!file.openFile(myGraph, name))
        QMessageBox::critical(this, tr("SearchProjectGUI - by Daniel San"),
                              tr("O arquivo nao pode ser aberto para leitura."));
    else {
        ui->lcdNumber->display(0);
        drawMatrix();
        ui->startButton->setEnabled(true);
    }
}

void Widget::drawMatrix() {
    int i, j;
    scene->clear();
    for(i = 0; i < 250; ++i) {
        for(j = 0; j < 250; ++j) {
            matrix = new MyMatrix(i, j, myGraph.getValue(i, j));
            scene->addItem(matrix);
        }
    }
}

void Widget::on_startButton_clicked() {
    bool flag = !fetchType.search(myGraph);
    drawMatrix();
    if(flag)
        QMessageBox::critical(this, tr("SearchProjectGUI - by Daniel San"),
                              tr("Nao foi possivel achar um caminho!"));
    ui->lcdNumber->display(fetchType.getSteps());
    ui->startButton->setEnabled(false);
}

void Widget::on_openButton_clicked() {
    myGraph.clear();
//    if (!qgetenv("QT_NO_NATIVE_FILEDIALOGS").isEmpty()) {
//        qt_filedialog_open_filename_hook = 0;
//        qt_filedialog_open_filenames_hook = 0;
//        qt_filedialog_save_filename_hook = 0;
//        qt_filedialog_existing_directory_hook = 0;
//    }

    QString fileName = QFileDialog::getOpenFileName();
    loadTextFile(fileName);
}

void Widget::on_genetareButton_clicked() {
    int inicio = 1, fim = 1, buracos = 20000, buracosLinha, i, j, linha = -(ui->spinBox->value());
    ui->lcdNumber->display(0);
    myGraph.clear();
    for (i = 0; i < 250; ++i) {
        buracosLinha = rand() % ui->spinBox_2->value();
        for (j = 0; j < 250; ++j) {
            if (inicio != 0 && rand() % 10000 == 10 && i > linha + ui->spinBox->value()) {
                myGraph.addVvertex('I', i, j);
                myGraph.setInit(i, j);
                --inicio;
                linha = i;
            }
            else if (fim != 0 && rand() % 10000 == 10 && i > linha + ui->spinBox->value()) {
                myGraph.addVvertex('F', i, j);
                myGraph.setEnd(i, j);
                --fim;
                linha = i;
            }
            else if (buracosLinha != 0 && buracos != 0 && rand() % 100 > 90) {
                myGraph.addVvertex('#', i, j);
                --buracosLinha;
                --buracos;
            }
            else
                myGraph.addVvertex(' ', i, j);
        }
    }
    drawMatrix();
    ui->startButton->setEnabled(true);
}

void Widget::on_aStarButton_clicked() {
    aStar = true;
    dijkstra = false;
}

void Widget::on_dijkstraButton_clicked() {
    dijkstra = true;
    aStar = true;
}
