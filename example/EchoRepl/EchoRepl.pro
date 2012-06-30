#-------------------------------------------------
#
# Project created by QtCreator 2012-06-30T18:28:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EchoRepl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
FORMS    += mainwindow.ui

LIBS += ../../libReplWidgetPlugin.so
INCLUDEPATH += ../../
