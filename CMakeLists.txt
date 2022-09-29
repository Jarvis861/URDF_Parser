CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(urdfparser)

FIND_PACKAGE(Boost REQUIRED)

SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++11")

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIR}
)

OPTION(URDF_BUILD_TEST "enable testing of library" OFF)

SET( URDF_SRCS
  src/common.cpp
  src/joint.cpp
  src/geometry.cpp
  src/link.cpp
  src/model.cpp
  src/tinyxml.cpp
  src/tinyxmlerror.cpp
  src/tinyxmlparser.cpp
)

ADD_LIBRARY( urdfparser SHARED
  ${URDF_SRCS}
)

SET(URDFPARSER_LIB urdfparser)

SET_PROPERTY(TARGET urdfparser PROPERTY POSITION_INDEPENDENT_CODE ON)

IF(URDF_BUILD_TEST) 
  include_directories(".")  # include catch.hpp
  
  ADD_EXECUTABLE(parse_simple test/parse_simple.cpp)
  TARGET_LINK_LIBRARIES(parse_simple urdfparser)

  ADD_EXECUTABLE(load_file test/load_file.cpp)
  TARGET_LINK_LIBRARIES(load_file urdfparser)

ENDIF(URDF_BUILD_TEST)
