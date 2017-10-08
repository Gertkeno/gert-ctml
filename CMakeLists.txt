cmake_minimum_required(VERSION 3.6)
project( gert-ctml )

include_directories( src )
file( GLOB SOURCES src/*.cpp )
MESSAGE(STATUS ${SOURCES})
add_executable( gert-ctml ${SOURCES} )
