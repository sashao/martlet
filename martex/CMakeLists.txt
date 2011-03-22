project(martex)

find_package(Qt4 REQUIRED)
set( QT_USE_QTGUI   FALSE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})

QT4_WRAP_CPP( SRCS ${HDRS} )

add_executable(martex ${SRCS} ${HDRS} )
add_dependencies(martex martletcommon qnetworkrpc)


target_link_libraries(martex qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES} )

