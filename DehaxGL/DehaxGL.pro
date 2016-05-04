#-------------------------------------------------
#
# Project created by QtCreator 2016-04-21T08:03:39
#
#-------------------------------------------------

QT       -= gui

TARGET = DehaxGL
TEMPLATE = lib

DEFINES += DEHAXGL_LIBRARY

SOURCES += DehaxGL.cpp \
    Model/Vertex.cpp \
    Math/Vec3i.cpp \
    Math/Vec3f.cpp \
    Math/Vec2i.cpp \
    Math/Matrix.cpp \
    Model/Face.cpp \
    Model/Mesh.cpp \
    Scene.cpp \
    Model/Model.cpp \
    Camera.cpp \
    Math/Vec4f.cpp \
    Model/ModelsFactory.cpp

HEADERS += DehaxGL.h\
        dehaxgl_global.h \
    IViewport.h \
    Model/Vertex.h \
    Utils/Utils.h \
    Math/Vec3i.h \
    Math/Vec3f.h \
    Math/Vec2i.h \
    Math/Matrix.h \
    Model/Face.h \
    Model/Mesh.h \
    Scene.h \
    Model/Model.h \
    Camera.h \
    Math/Vec4f.h \
    Model/ModelsFactory.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#QMAKE_CXXFLAGS_DEBUG *= -pg
#QMAKE_LFLAGS_DEBUG *= -pg

#CONFIG += debug
