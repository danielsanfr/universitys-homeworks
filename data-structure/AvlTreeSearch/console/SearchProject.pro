QT += core
QT -= gui

CONFIG += c++11

TARGET = SearchProject
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    myfile.cpp \
    myavltree.cpp \
    arraylist.cpp

HEADERS += \
    node.h \
    myfile.h \
    myavltree.h \
    arraylist.h
