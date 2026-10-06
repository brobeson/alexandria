add_library(alexandria.alexandria INTERFACE)
add_library(alexandria::alexandria ALIAS alexandria.alexandria)
target_sources(
  alexandria.alexandria
  INTERFACE
  FILE_SET HEADERS
  FILES
    alexandria/angle.hpp
    alexandria/errors.hpp
    alexandria/interval.hpp
    alexandria/thread_safe.hpp
)
