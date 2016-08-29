#include "textfinder.h"
#include "ui_textfinder.h"

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


TextFinder::TextFinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextFinder)
{
    ui->setupUi(this);
}

TextFinder::~TextFinder()
{
    delete ui;
    /*1º build em 07 de Maio de 2012*/
    QMessageBox::information(this, tr("About SearchProjectGUI"),
                                       tr("SearchProjectGUI 1.0\n"
                                          "Compilado em: 15 de Maio de 2012\n"
                                          "Desenvolvido por: Daniel San Ferreira da Rocha\n"
                                          "Colaborador do COMPE\n(Laboratorio de Computacao Pervasiva)"));
}

void TextFinder::on_openButton_clicked()
{
//    if (!qgetenv("QT_NO_NATIVE_FILEDIALOGS").isEmpty()) {
//        qt_filedialog_open_filename_hook = 0;
//        qt_filedialog_open_filenames_hook = 0;
//        qt_filedialog_save_filename_hook = 0;
//        qt_filedialog_existing_directory_hook = 0;
//    }

    QString filename = QFileDialog::getOpenFileName();
    loadTextFile(filename);
    //qDebug() << filename;
}

void TextFinder::on_findButton_clicked()
{
    QString searchString = ui->lineEdit->text();
    if(word != searchString)
    {
        //qDebug() << searchString;
        word = searchString;
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
    }
    ui->textEdit->find(searchString, QTextDocument::FindWholeWords);
    file.searchWord(searchString.toStdString());
    if(file.fraseSaida == "A palavra pesquisada nao foi localizada!" || file.fraseSaida == "Nenhum arquivo foi carregado ainda!")
        QMessageBox::warning(this, tr("SearchProjectGUI - by Daniel San"),
                                           searchString.fromStdString(file.fraseSaida));
    else
        QMessageBox::information(this, tr("SearchProjectGUI - by Daniel San"),
                                           searchString.fromStdString(file.fraseSaida));
    //qDebug() << searchString.fromStdString(file.fraseSaida);
}

void TextFinder::loadTextFile(QString filename)
{
    QFile inputFile(filename);
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->textEdit->setPlainText(line);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);

    QByteArray ba = filename.toLocal8Bit();
    char * fileName = ba.data();
    if(!file.openFile(fileName))
        QMessageBox::critical(this, tr("SearchProjectGUI - by Daniel San"),
                              tr("O arquivo não pode ser aberto para leitura.\n"
                                 "Programa terminando...\n"));
}
