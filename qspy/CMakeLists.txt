project(qspy)

find_package(Qt4 REQUIRED)

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})
file(GLOB UI *.ui)

QT4_WRAP_CPP( SRCS ${HDRS} )
QT4_WRAP_UI( UI_H ${UI} )

add_executable(qspy ${SRCS} ${HDRS} ${UI_H} )
add_dependencies(qspy martletcommon qnetworkrpc)

target_link_libraries(qspy qnetworkrpc martletcommon ${QT_LIBRARIES} ${Boost_LIBRARIES})

