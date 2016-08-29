QT += core
QT -= gui

CONFIG += c++11

TARGET = AStarShortPath
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myfile.cpp \
    linkedlist.cpp \
    graph.cpp \
    cell.cpp \
    astaralgorithm.cpp

HEADERS  += \
    myfile.h \
    linkedlist.h \
    graph.h \
    cell.h \
    astaralgorithm.h
