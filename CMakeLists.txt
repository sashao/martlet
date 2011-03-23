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
#find_package(Boost REQUIRED COMPONENTS serialization)
set( Boost_LIBRARIES "libboost_serialization-mgw44-mt-d-1_46_1.a")
set( HREGEXP "*.h" )

include( ${QT_USE_FILE} )
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${QT_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${COMMON_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/third_party"
        "C:\\Qt\\boost_1_46_1\\"
        )
link_directories( "${CMAKE_BINARY_DIR}/bin" "C:\\Qt\\boost_1_46_1\\stage\\lib\\")
SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(examples/QtImageCut)

add_subdirectory(martletcommon)
add_subdirectory(martlet)
add_subdirectory(martex)
add_subdirectory(martex/libqtload)
add_subdirectory(qspy)
add_subdirectory(third_party/qnetworkrpc/src)


