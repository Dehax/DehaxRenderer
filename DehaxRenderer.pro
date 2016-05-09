TEMPLATE = subdirs

SUBDIRS += \
    DehaxGL \
    DehaxRenderer

CONFIG += ordered

#QMAKE_CXXFLAGS_DEBUG *= -pg
#QMAKE_LFLAGS_DEBUG *= -pg

DEFINES *= QT_USE_QSTRINGBUILDER
