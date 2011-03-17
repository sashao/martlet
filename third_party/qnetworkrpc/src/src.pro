
include(../config.pri)

CONFIG(MSVC){
}
CONFIG(GCC) {
}

QT       -= gui

TARGET = qnetworkrpc
DESTDIR = ../lib
TEMPLATE = lib

SOURCES += \
    QAbstractCommand.cpp \
    QRemoter.cpp \
    QRemoterSignalsWatcer.cpp \
    QAbstractProtocol.cpp \
    QStringProtocol.cpp


HEADERS += \
    QAbstractCommand.h \
    QRemoter.h \
    QRemoterSignalsWatcer.h \
    QStringProtocol.h \
    QAbstractProtocol.h

include (../../../globinclude.pri)

#TRANSLATIONS = $$GLOBTRANS
#RESOURCES   += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin
