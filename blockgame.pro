#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T10:24:40
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blockgame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    block.cpp \
    blockgame.cpp

HEADERS  += mainwindow.h \
    block.h \
    blockgame.h

FORMS    += mainwindow.ui
