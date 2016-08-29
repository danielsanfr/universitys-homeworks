#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T14:59:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AStarShortPathGUI
TEMPLATE = app

SOURCES += main.cpp\
    widget.cpp \
    myfile.cpp \
    linkedlist.cpp \
    graph.cpp \
    cell.cpp \
    astaralgorithm.cpp \
    mymatrix.cpp

HEADERS  += widget.h \
    myfile.h \
    linkedlist.h \
    graph.h \
    cell.h \
    astaralgorithm.h \
    mymatrix.h

FORMS    += widget.ui
