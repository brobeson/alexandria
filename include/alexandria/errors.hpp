#ifndef ALEXANDRIA_ERRORS_HPP
#define ALEXANDRIA_ERRORS_HPP

// iterating range: https://godbolt.org/z/4bGY9fn7n
// errors example: https://godbolt.org/z/ssq6oGd1d
// TODO Stringify the actual condition values?

#include <stdexcept>

namespace alex {
  struct unmet_expectation: public std::logic_error {
    explicit unmet_expectation(const char* const message):
      std::logic_error(message) {}
  };
}

#define ALEX_STRINGIFY_DETAIL(x) #x
#define ALEX_STRINGIFY(x) ALEX_STRINGIFY_DETAIL(x)

#define ALEX_EXPECTS( condition) \
  if (!(condition)) [[unlikely]] {            \
    throw alex::unmet_expectation{#condition " (at " __FILE__ ":" ALEX_STRINGIFY(__LINE__) ")"};            \
  }
