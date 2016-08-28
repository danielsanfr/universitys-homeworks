#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T20:58:27
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = PushAnything
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    peer.cpp \
    Util.cpp \
    discoverypeer.cpp \
    peermodel.cpp \
    announcer.cpp \
    textmessage.cpp \
    pushanythingtcpsocket.cpp \
    pullanythingtcpsocket.cpp \
    filemessage.cpp \
    maintestthread.cpp

HEADERS += \
    peer.hpp \
    Util.hpp \
    message.hpp \
    discoverypeer.hpp \
    peermodel.hpp \
    announcer.hpp \
    textmessage.hpp \
    pushanythingtcpsocket.hpp \
    pullanythingtcpsocket.hpp \
    filemessage.hpp \
    maintestthread.hpp
