CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT( gert-ctml )

SET( CMAKE_CXX_STANDARD 11 )
INCLUDE_DIRECTORIES( src )
FILE( GLOB SOURCES src/*.cpp )
MESSAGE(STATUS ${SOURCES})
ADD_EXECUTABLE( gert-ctml ${SOURCES} )
