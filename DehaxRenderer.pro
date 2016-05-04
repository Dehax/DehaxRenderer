TEMPLATE = subdirs

SUBDIRS += \
    DehaxGL \
    DehaxRenderer

CONFIG += ordered

DEFINES *= QT_USE_QSTRINGBUILDER
