project(libqtload)

find_package(Qt4 REQUIRED)

set( QT_USE_QTGUI   TRUE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS *.h)
file(GLOB UI *.ui)

QT4_WRAP_CPP(SRCS ${HDRS})
QT4_WRAP_UI( HUI ${UI} )

#if (WIN32)
#  add_definitions(-DLIB_EXPORTS)
#endif(WIN32)

add_library(libqtload SHARED ${SRCS})


