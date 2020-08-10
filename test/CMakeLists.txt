# CMake file for test directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/test")

file(GLOB_RECURSE PROJECT_SRC ${CMAKE_SOURCE_DIR}/lib/libppars/src/*.cpp)

addtest("alltests"
  testcsv.cpp
  ${PROJECT_SRC}
)
