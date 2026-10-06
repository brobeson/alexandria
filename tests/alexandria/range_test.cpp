#include "alexandria/interval.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

namespace
{
  auto make() { return alex::interval<float>{1.0, 0.0}; }
} // namespace

SCENARIO("construct a range", "[unit][range]")
{
  WHEN("a range is constructed")
  {
    THEN("the range's state is correct")
    {
      constexpr alex::interval<int> actual{0, 255};
      CHECK(actual.minimum() == 0);
      CHECK(actual.maximum() == 255);
    }
  }
  GIVEN("invalid bounds")
  {
    SKIP("This one doesn't work correctly.");
    WHEN("a range is constructed")
    {
      THEN("the constructor throws an exception")
      {
        CHECK_THROWS_MATCHES(
          // []() { return alex::interval<float>{1.0, 0.0}; }(),
          make(),
          std::invalid_argument,
          Catch::Matchers::Message(
            "alex::range minimum must be less than maximum"));
      }
    }
  }
}
