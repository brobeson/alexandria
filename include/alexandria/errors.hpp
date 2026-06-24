#ifndef ALEXANDRIA_ERRORS_HPP
#define ALEXANDRIA_ERRORS_HPP

#include <stdexcept>

#ifndef ALEX_ASSERT
#define ALEX_ASSERT(condition) \
  if (!(condition)) { \
    throw std::runtime_error{#condition}; \
  }
#endif
