cmake_minimum_required(VERSION 4.4)
project(
  alexandria
  VERSION 0.0.0
  DESCRIPTION "A general purpose C++ library"
  HOMEPAGE_URL "https://github.com/brobeson/alexandria"
  LANGUAGES CXX
  SPDX_LICENSE MIT
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(include)

option(
  BUILD_TESTING
  "Enable or disable building Alexandria tests"
  ${PROJECT_IS_TOP_LEVEL}
)
enable_testing()
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
