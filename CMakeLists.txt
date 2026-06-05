cmake_minimum_required(VERSION 4.0)
project(alexandria LANGUAGES CXX)

add_subdirectory(include)

option(ALEXANDRIA_BUILD_TESTS "Enable or disable building tests." ${PROJECT_IS_TOP_LEVEL})
if(ALEXANDRIA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
