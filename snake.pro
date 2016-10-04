#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T00:58:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    snakeframe.cpp \
    bfs.cpp

HEADERS  += mainwindow.h \
    snakeframe.h \
    bfs.h \
    global.h

FORMS    += mainwindow.ui
