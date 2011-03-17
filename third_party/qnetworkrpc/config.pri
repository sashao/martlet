
# linux+g++ and windows-qt-sdk
CONFIG+=GCC
# visual studio tools usage
#CONFIG+=MSVC


QT += network

VERSION=0.8.3

# comment this line if you want dynamic library to be build
#CONFIG += staticlib 
CONFIG += debug

include (../../globinclude.pri)

#TRANSLATIONS = $$GLOBTRANS
#RESOURCES   += $$GLOBRESOURCES
DESTDIR = $$GLOBTOP/bin
