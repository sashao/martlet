#-------------------------------------------------
#
# Project created by QtCreator 2010-01-31T17:05:55
#
#-------------------------------------------------

QT       += network script xml

TARGET = martlet
TEMPLATE = app


SOURCES += main.cpp\
        MartletWindow.cpp

HEADERS  += MartletWindow.h

FORMS    += MartletWindow.ui





include (../globinclude.pri)

TRANSLATIONS = $$GLOBTRANS
RESOURCES   += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin

INCLUDEPATH += $$THIRDPARTYDIR $$MARTLETCOMMONDIR
LIBS += -lmartletcommon -lqxmlrpc
LIBPATH += $$GLOBTOP/bin
