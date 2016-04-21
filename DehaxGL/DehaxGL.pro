#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T08:03:39
#
#-------------------------------------------------

QT       -= gui

TARGET = DehaxGL
TEMPLATE = lib

DEFINES += DEHAXGL_LIBRARY

SOURCES += DehaxGL.cpp

HEADERS += DehaxGL.h\
        dehaxgl_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
