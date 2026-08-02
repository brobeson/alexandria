if(NOT TARGET Catch2::Catch2WithMain)
  include("${alexandria_SOURCE_DIR}/cmake/CPM.cmake")
  CPMAddPackage("gh:catchorg/Catch2@3.15.0" SYSTEM)
  list(APPEND CMAKE_MODULE_PATH $"{Catch2_SOURCE_DIR}/extras")
endif()
include(Catch)
set(TESTS angle animation_clock range)
foreach(TEST IN LISTS TESTS)
  add_executable(alexandria.test.${TEST} ${TEST}_test.cpp)
  target_link_libraries(
    alexandria.test.${TEST}
    PRIVATE alexandria::alexandria Catch2::Catch2WithMain
  )
  catch_discover_tests(alexandria.test.${TEST} ADD_TAGS_AS_LABELS)
endforeach()
