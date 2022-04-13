project(houselight)
include(ExternalProject)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -O3")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -pedantic -O0 -g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(VERBOSE "debug" OFF)
if (VERBOSE)
  add_definitions("-DDEBUG")
endif (VERBOSE)

ExternalProject_Add(hueplusplus
  PREFIX external/hueplusplus
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/hueplusplus
  BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/build-hueplusplus
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/install-hueplusplus
  CONFIGURE_COMMAND cmake ./ -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> 
  BUILD_COMMAND make -j4
  INSTALL_COMMAND make install
  EXCLUDE_FROM_ALL 1
  )

add_subdirectory(external/googletest EXCLUDE_FROM_ALL)

set(hueplusplus_LIBPATH "external/install-hueplusplus/lib")
set(hueplusplus_INCLUDE "external/install-hueplusplus/include")

add_executable(houselight
  main.cpp
  )

add_dependencies(houselight hueplusplus)

link_directories(houselight ${hueplusplus_LIBPATH})
target_include_directories(houselight PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(houselight PUBLIC ${hueplusplus_INCLUDE})
target_link_libraries(houselight PUBLIC ${hueplusplus_LIB})

#target_link_libraries(main houselight)

#add_subdirectory(test)
