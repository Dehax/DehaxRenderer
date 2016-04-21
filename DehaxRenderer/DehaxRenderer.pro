#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T08:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DehaxRenderer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Widgets/Viewport.cpp

HEADERS  += MainWindow.h \
    Widgets/Viewport.h

FORMS    += MainWindow.ui
