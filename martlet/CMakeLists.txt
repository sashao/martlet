project(martlet)

find_package(Qt4 REQUIRED)

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI *.ui)
file(GLOB RSC "${CMAKE_SOURCE_DIR}/resources/*.qrc")


QT4_WRAP_CPP( SRCS ${HDRS} )
QT4_WRAP_UI( UI_H ${UI} )
QT4_ADD_RESOURCES( RSRC ${RSC} )

ADD_EXECUTABLE( martlet WIN32 ${SRCS} ${HDRS} ${UI_H} ${RSRC} )
ADD_DEPENDENCIES( martlet martletcommon qnetworkrpc )

#include_directories(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES( "${CMAKE_BINARY_DIR}/bin" ${BOOST_LIBDIR})
TARGET_LINK_LIBRARIES(martlet qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} martletcommon)
#TARGET_LINK_LIBRARIES( ${PROGNAME} ${QT_LIBRARIES} libQtGui4.a)
