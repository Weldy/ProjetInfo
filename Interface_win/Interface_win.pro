#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T18:14:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface_win
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    structures.h \
    include.h

FORMS    += mainwindow.ui

CONFIG += c++11
