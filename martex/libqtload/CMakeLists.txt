project(qtload)

find_package(Qt4 REQUIRED)

set( QT_USE_QTGUI   TRUE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI "${CMAKE_CURRENT_SOURCE_DIR}/*.ui")

QT4_WRAP_CPP(SRCS ${HDRS})
QT4_WRAP_UI( UI_H ${UI} )

add_library(QtLoad SHARED ${SRCS} ${UI_H})
target_link_libraries(QtLoad qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} )


