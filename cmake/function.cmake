# Functions for dressing "life" :)

##
function(addtest TESTNAME FIRSTSOURCE)
  add_executable(${TESTNAME} main.cpp ${FIRSTSOURCE} ${ARGN})
  target_include_directories(${TESTNAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
  
  if(WIN32)
    target_link_libraries(${TESTNAME} wsock32 ws2_32)
  else()
    target_link_libraries(${TESTNAME} pthread)
  endif()

  add_test(
    NAME ${TESTNAME}
    COMMAND ${CMAKE_COMMAND} --build . --target ${TESTNAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )
  set_target_properties(${TESTNAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_bin
  )
endfunction(addtest)

