cmake_minimum_required(VERSION 4.2)
project(
  alexandria
  VERSION 0.0.0
  DESCRIPTION "A general purpose C++ library"
  HOMEPAGE_URL "https://github.com/brobeson/alexandria"
  LANGUAGES CXX
  # SPDX_LICENSE MIT
)

add_subdirectory(include)

option(
  ALEXANDRIA_BUILD_TESTS
  "Enable or disable building Alexandria tests"
  ${PROJECT_IS_TOP_LEVEL}
)
if(ALEXANDRIA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
