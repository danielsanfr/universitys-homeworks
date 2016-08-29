#-------------------------------------------------
#
# Project created by QtCreator 2012-05-06T22:09:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SearchProjectGUI
TEMPLATE = app

SOURCES += main.cpp \
    textfinder.cpp \
    node.cpp \
    myfile.cpp \
    myavltree.cpp \
    arraylist.cpp

HEADERS += \
    textfinder.h \
    node.h \
    myfile.h \
    myavltree.h \
    arraylist.h

FORMS    += textfinder.ui

RESOURCES += \
    textfinder.qrc
