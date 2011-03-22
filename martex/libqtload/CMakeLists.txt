project(qtload)

find_package(Qt4 REQUIRED)

set( QT_USE_QTGUI   TRUE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI *.ui)

QT4_WRAP_CPP(SRCS ${HDRS})
QT4_WRAP_UI( UIH ${UI} )

add_library(QtLoad SHARED ${SRCS})


