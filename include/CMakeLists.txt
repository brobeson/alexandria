add_library(alexandria.alexandria INTERFACE)
add_library(alexandria::alexandria ALIAS alexandria.alexandria)
target_compile_features(alexandria.alexandria INTERFACE cxx_std_20)
target_sources(
  alexandria.alexandria
  INTERFACE
  FILE_SET HEADERS
  FILES
    alexandria/angle.hpp
    alexandria/errors.hpp
    alexandria/range.hpp
    alexandria/thread_safe.hpp
)
