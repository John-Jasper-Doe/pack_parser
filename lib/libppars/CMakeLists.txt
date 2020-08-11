# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/libppars")

set(LIB_NAME ppars)
file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_library(${LIB_NAME} SHARED ${ALL_CXX_SOURCE_FILES})
target_include_directories(${LIB_NAME} PRIVATE ${LIBRARY_INCLUDE_PATH})
target_link_libraries(${LIB_NAME} pthread)

set_target_properties(
  ${LIB_NAME}
  PROPERTIES
    PUBLIC_HEADER ${LIBRARY_INCLUDE_PATH}/libppars/ppars.hpp
)

install(
  TARGETS ${LIB_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
