#ifndef ALEXANDRIA_ERRORS_HPP
#define ALEXANDRIA_ERRORS_HPP

// iterating range: https://godbolt.org/z/4bGY9fn7n
// errors example: https://godbolt.org/z/ssq6oGd1d
// TODO Stringify the actual condition values?

#include <stdexcept>

namespace alex {
  /// Thrown when a function precondition or class invariant fails.
  struct unmet_expectation: public std::logic_error {
    /**
     * \brief Construct an unmet_expection exception.
     * \param[in] message An explanation of the failed precondition or invariant.
     */
    explicit unmet_expectation(const char* const message):
      std::logic_error(message) {}
  };
}

// Implementation details, equivalent to namespace alex::detail.
#define ALEX_DETAIL_STRINGIFY_DETAIL(x) #x
#define ALEX_DETAIL_STRINGIFY(x) ALEX_DETAIL_STRINGIFY_DETAIL(x)

/**
 * \brief Check a function precondition or class invariant.
 * \param[in] condition A boolean expression representing the precondition or
 * invariant. `false` indicates failure of the condition.
 * \throws alex::unmet_expectation if \a condition is `false`
 * \warning This macro assumes the condition is pass more often that fail. It
 * uses `[[unlikely]]` for the failure case. You should profile your code to
 * ensure this assumption doesn't deoptimize your code.
 */
#define ALEX_EXPECTS(condition) \
  if (!(condition)) [[unlikely]] {            \
    throw alex::unmet_expectation{#condition " (at " __FILE__ ":" ALEX_DETAIL_STRINGIFY(__LINE__) ")"};            \
  }
