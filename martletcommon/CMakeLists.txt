project(martletcommon)

find_package(Qt4 REQUIRED)

set( QT_USE_QTGUI   TRUE )

file(GLOB MC_SRCS *.cpp)
file(GLOB MC_HDRS *.h)

QT4_WRAP_CPP(MC_SRCS ${MC_HDRS})

#if (WIN32)
#  add_definitions(-DLIB_EXPORTS)
#endif(WIN32)

add_library(martletcommon SHARED ${MC_SRCS})

#set_target_properties(martletcommon PROPERTIES SOVERSION "${PROPERTYEDITOR_VERSION_MAJOR}.${PROPERTYEDITOR_VERSION_MINOR}"
#                                                VERSION ${PROPERTYEDITOR_VERSION})
#target_link_libraries(martletcommon ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} )

#install(TARGETS PropertyEditor ${INSTALL_TARGETS_DEFAULT_ARGS} )
#install(FILES propertyeditor.h propertyinterface.h propertyvalidator.h DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)
