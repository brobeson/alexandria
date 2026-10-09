add_executable(alexandria.test.alpha)
target_sources(alexandria.test.alpha PRIVATE alpha.cpp)
add_test(NAME alexandria.test.alpha COMMAND alexandria.test.alpha)