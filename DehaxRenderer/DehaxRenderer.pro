#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T08:01:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DehaxRenderer
TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG *= -pg
QMAKE_LFLAGS_DEBUG *= -pg

SOURCES += main.cpp\
        MainWindow.cpp \
    Widgets/Viewport.cpp

HEADERS  += MainWindow.h \
    Widgets/Viewport.h

FORMS    += MainWindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../DehaxGL/release/ -lDehaxGL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../DehaxGL/debug/ -lDehaxGL
else:unix: LIBS += -L$$OUT_PWD/../DehaxGL/ -lDehaxGL

INCLUDEPATH += $$PWD/../DehaxGL
DEPENDPATH += $$PWD/../DehaxGL
