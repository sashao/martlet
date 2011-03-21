project(martex)

find_package(Qt4 REQUIRED)
set( QT_USE_QTGUI   FALSE )

file(GLOB MT_SRCS *.cpp)
file(GLOB MT_HDRS ${HREGEXP})

QT4_WRAP_CPP( MT_SRCS ${MT_HDRS} )

add_executable(martex ${MT_SRCS} ${MT_HDRS} )
add_dependencies(martex martletcommon qnetworkrpc)


target_link_libraries(martex qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES} )

