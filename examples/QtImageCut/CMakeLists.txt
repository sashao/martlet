project(QtImageCut)

find_package(Qt4 REQUIRED)
set( QT_USE_QTGUI   TRUE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI *.ui)

QT4_WRAP_CPP( SRCS ${HDRS} )
QT4_WRAP_UI( UI_H ${UI} )

add_executable(QtImageCut ${SRCS} ${HDRS} ${UI_H})

target_link_libraries(QtImageCut ${QT_LIBRARIES} )

SET(EXECUTABLE_OUTPUT_PATH ".")
