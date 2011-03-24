cmake_minimum_required(VERSION 2.6)
project(martlet-package)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (VERSION_MAJOR 2)
set (VERSION_MINOR 1)
set (VERSION_RELEASE 3)
set (VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_RELEASE}" )

set (COMMON_DIR martletcommon)
set (MARTLET_DIR martlet)
set (RPC_DIR third_party/qnetworkrpc/src)

#add_definitions (-DPROPERTYEDITOR_VERSION=\"${PROPERTYEDITOR_VERSION}\")

set( QT_USE_QTGUI   TRUE )
set( QT_USE_QTNETWORK   TRUE )

find_package(Qt4 REQUIRED)
set( BOOST_DIR "") # sustem by default

IF (UNIX)  # All unix-like OS's, including Apple OS X (and Cygwin)
    find_package(Boost REQUIRED COMPONENTS serialization)
    add_definitions ("-D__declspec\\(dllexport\\)=" "")
ELSEIF (WIN32 OR MINGW) # All windows versions (including Cygwin)
                # Mingw compiler on windows
    set( Boost_LIBRARIES "libboost_serialization-mgw44-mt-d-1_46_1.a")
    set( BOOST_DIR "C:\\Qt\\boost_1_46_1")
    set( Boost_LIBDIR "${BOOST_DIR}\\stage\\lib\\")
ELSE (MSVC)  # Microsoft compiler on windows
ENDIF()

set( HREGEXP "*.h" )

include( ${QT_USE_FILE} )
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${QT_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${COMMON_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
        ${BOOST_DIR}
        )
link_directories( "${CMAKE_BINARY_DIR}/bin" ${BOOST_LIBDIR})
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(examples/QtImageCut)

add_subdirectory(martletcommon)
add_subdirectory(martlet)
add_subdirectory(martex)
add_subdirectory(martex/libqtload)
add_subdirectory(qspy)
add_subdirectory(third_party/qnetworkrpc/src)


