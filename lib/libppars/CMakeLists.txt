# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/libppars")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_library(ppars SHARED ${ALL_CXX_SOURCE_FILES})
target_include_directories(ppars PRIVATE ${LIBRARY_INCLUDE_PATH})
target_link_libraries(ppars pthread)

set_target_properties(
  ppars
  PROPERTIES
    PUBLIC_HEADER ${LIBRARY_INCLUDE_PATH}/libppars/ppars.hpp
)
