cmake_minimum_required(VERSION 2.6)

project(qnetworkrpc)

find_package(Qt4 REQUIRED)

set( QT_USE_QTGUI   FALSE )

file(GLOB SRCS *.cpp)
file(GLOB HDRS ${HREGEXP})

QT4_WRAP_CPP(SRCS ${HDRS})

add_library(qnetworkrpc SHARED ${SRCS})

#set_target_properties(martletcommon PROPERTIES SOVERSION "${PROPERTYEDITOR_VERSION_MAJOR}.${PROPERTYEDITOR_VERSION_MINOR}"
#                                                VERSION ${PROPERTYEDITOR_VERSION})
#target_link_libraries(martletcommon ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} )

#install(TARGETS PropertyEditor ${INSTALL_TARGETS_DEFAULT_ARGS} )
#install(FILES propertyeditor.h propertyinterface.h propertyvalidator.h DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)
