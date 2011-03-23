project(martlet)

find_package(Qt4 REQUIRED)

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI *.ui)
file(GLOB RSC "${CMAKE_SOURCE_DIR}/resources/*.qrc")


QT4_WRAP_CPP( SRCS ${HDRS} )
QT4_WRAP_UI( UI_H ${UI} )
QT4_ADD_RESOURCES( RSRC ${RSC} )

add_executable(martlet ${SRCS} ${HDRS} ${UI_H} ${RSRC} )
add_dependencies(martlet martletcommon qnetworkrpc )

#include_directories(${Boost_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(martlet qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY})
#TARGET_LINK_LIBRARIES( ${PROGNAME} ${QT_LIBRARIES} libQtGui4.a)
