
TEMPLATE = lib
TARGET = QtLoad
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += designer
CONFIG += uitools

win32:LIBS += User32.lib

qtAddLibrary(QtDesigner)
qtAddLibrary(QtDesignerComponents)

QT += xml network

# Input
SOURCES += lib.cpp \
    filter.cpp \
    qspywidget.cpp
HEADERS += filter.h \
    qspywidget.h


FORMS += qspywidget.ui

include (../../globinclude.pri)

INCLUDEPATH += $$MARTLETCOMMONDIR
INCLUDEPATH += $$THIRDPARTYDIR

TRANSLATIONS = $$GLOBTRANS
RESOURCES   += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin

CONFIG +=link_pkgconfig
PKGCONFIG = boost_serialization
LIBPATH += $$GLOBTOP/bin
LIBS += -lmartletcommon \
    -lqxmlrpc \
    -lloki \
    -lboost_serialization
