# -------------------------------------------------
# Project created by QtCreator 2010-01-31T17:05:55
# -------------------------------------------------
QT += network \
    script \
    xml
TARGET = martlet
TEMPLATE = app
CONFIG += debug
SOURCES += main.cpp \
    MartletWindow.cpp \
    ProjectDialog.cpp \
    AppSettingsDialog.cpp \
    MProjectModel.cpp
HEADERS += MartletWindow.h \
    ProjectDialog.h \
    AppSettingsDialog.h \
    MProjectModel.h
FORMS += MartletWindow.ui \
    ProjectDialog.ui \
    AppSettingsDialog.ui
include (../globinclude.pri)
TRANSLATIONS = $$GLOBTRANS
RESOURCES += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin
INCLUDEPATH += $$MARTLETCOMMONDIR
INCLUDEPATH += $$THIRDPARTYDIR
DEPENDPATH += . \
              $$GLOBTOP/martex

# message(Martlet common dir !!!!!!!!!  $$MARTLETCOMMONDIR $$THIRDPARTYDIR $$GLOBTOP)
CONFIG +=link_pkgconfig
PKGCONFIG = boost_serialization
LIBPATH += $$GLOBTOP/bin
LIBS += -lmartletcommon \
    -lqxmlrpc \
    -lloki \
    -lboost_serialization
