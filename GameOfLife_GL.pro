#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T16:47:06
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameOfLife_GL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GLWidget.cpp

HEADERS  += mainwindow.h \
    GLWidget.h

FORMS    += mainwindow.ui
