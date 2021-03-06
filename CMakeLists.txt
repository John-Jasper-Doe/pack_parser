# Root CMake file for BULK SERVER Project
#
# Copyright John Doe 2020
# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file LICENSE.txt or https://opensource.org/licenses/BSD-3-Clause for details.

cmake_minimum_required(VERSION 3.8)

# Adding a path with "cmake" modules to the system search paths.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(print)
include(function)

##############################################################################
## Setting project.

include(version)
set(PACK_PARS_VERSION ${PACK_PARS_MAJOR}.${PACK_PARS_MINOR}.${PACK_PARS_PATCH})
configure_file(version.hpp.in ${CMAKE_BINARY_DIR}/src/include/version.hpp @ONLY)

set(PROJECT_NAME mts_test)
set(PROJECT_VERSION ${PACK_PARS_MAJOR}.${PACK_PARS_MINOR}.${PACK_PARS_PATCH})
set(PROJECT_DESCRIPTION "")

project(
  ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  DESCRIPTION ${PROJECT_DESCRIPTION}
  LANGUAGES CXX
)

print("PROJECT: ${PROJECT_NAME}")
print("VERSION: ${PROJECT_VERSION}")
print("DESCRIPTION: ${PROJECT_DESCRIPTION}")

# Output ...
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/lib/libppars/include)
include_directories(${LIBRARY_INCLUDE_PATH})

##############################################################################
## Set property
include(compiler)
include(GNUInstallDirs)

##############################################################################
## Setting options on project
option(CLANG_FORMAT "Enable clang-format target" ON)
option(DOCUMENTATION "Build documentation" ON)
option(TESTING "Build tests" ON)

if(CLANG_FORMAT)
  include(clang-format)
endif()

if(DOCUMENTATION)
  find_package(Doxygen COMPONENTS dot)
  include(doxygen)
endif()

# Settings for test cases.
if (TESTING)
  print("Target \"test\" enabled")
  include(CTest)
  add_subdirectory(test)
  enable_testing()
endif()

# Added directory
add_subdirectory(lib)
add_subdirectory(src)

# generate .deb package
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT john.jasper.doe@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

set(CPACK_PACKAGE_VERSION_MAJOR "${PACK_PARS_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PACK_PARS_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PACK_PARS_PATCH}")

# include will generate proper code for .deb generation
include(CPack)

