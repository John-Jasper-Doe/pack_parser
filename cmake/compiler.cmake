#   This module is required to configure the main parameters of the compiler.
#   Parameters are designed for various compilers.

print("Detecting and configuring the compiler ...")
print("Detected: ${CMAKE_CXX_COMPILER_ID} ver:${CMAKE_CXX_COMPILER_VERSION}")

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
print("C++ standard: ${CMAKE_CXX_STANDARD}")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  print("${CMAKE_BUILD_TYPE} mode")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Werror -Wextra -Wpedantic -g -O0)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-Wall -Werror -Wextra -Wpedantic -O2)
  endif()
# Using Visual Studio C++
elseif(MSVC)
  print("${CMAKE_BUILD_TYPE} mode")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(/W4 -g -O0)
  elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(/W4 -O2)
  endif()
else()
  fatal_error("You are using an unsupported compiler!")
endif()
