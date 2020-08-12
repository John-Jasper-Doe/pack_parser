# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/src")

file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.cpp *.cxx)

add_executable(${PROJECT_NAME} ${ALL_CXX_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32 ppars)
else()
  target_link_libraries(${PROJECT_NAME} pthread ppars)
endif()

# install to bin folder our binaries
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
