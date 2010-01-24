
TEMPLATE = lib
TARGET = QtLoad
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += designer
CONFIG += uitools

win32:LIBS += User32.lib

qtAddLibrary(QtDesigner)
qtAddLibrary(QtDesignerComponents)

QT += xml

# Input
SOURCES += lib.cpp \
    filter.cpp \
    qspywidget.cpp
HEADERS += filter.h \
    qspywidget.h


FORMS += qspywidget.ui

include (../../globinclude.pri)

TRANSLATIONS = $$GLOBTRANS
RESOURCES   += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin

