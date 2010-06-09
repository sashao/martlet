# #####################################################################
# Automatically generated by qmake (2.01a) Mon Jan 25 22:56:06 2010
# #####################################################################
TEMPLATE = lib
TARGET = martletcommon
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += warn_on
CONFIG += staticlib
CONFIG += debug
QT += xml
QT += network

# Input
HEADERS += AbstractCommand.h \
    AbstractEventFabric.h \
    AbstractObjectNameMapper.h \
    CSVCommand.h \
    CSVEventFabric.h \
    EventCatcher.h \
    ObjectNameMapper.h \
    MartletClient.h \
    MartletServer.h \
    MartletProject.h

SOURCES += AbstractCommand.cpp \
    AbstractEventFabric.cpp \
    AbstractObjectNameMapper.cpp \
    CSVCommand.cpp \
    CSVEventFabric.cpp \
    EventCatcher.cpp \
    ObjectNameMapper.cpp \
    MartletClient.cpp \
    MartletServer.cpp \
    MartletProject.cpp

include (../globinclude.pri)
TRANSLATIONS = $$GLOBTRANS
RESOURCES += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin
INCLUDEPATH += $$THIRDPARTYDIR
