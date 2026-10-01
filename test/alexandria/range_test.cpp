#include "alexandria/range.hpp"
#include <iostream>

int main()
{
  for (const auto i : alex::range{0, 10})
  {
    std::cout << i << '\n';
  }
  return EXIT_SUCCESS;
}