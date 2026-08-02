#include <catch2/catch_test_macros.hpp>

namespace
{
  class animation_clock
  {
  public:
    struct iterator
    {
      animation_clock* m_clock{nullptr};

      auto operator*() const
      {
        return m_clock->m_current;
      }

      bool operator!=(const iterator& b)
      {
        return false;
      }

      iterator& operator++(int)
      {
        m_clock->m_current++;
        return *this;
      }
    };

    animation_clock& start(const std::chrono::seconds& s)
    {
      m_start = s;
      return *this;
    }

    iterator begin()
    {
      return iterator{this};
    }

    iterator end()
    {
      return iterator{this};
    }

  private:
    std::chrono::seconds m_start{0};
    std::chrono::seconds m_stop{0};
    std::chrono::seconds m_current{0};
  };
} // namespace

SCENARIO("We can loop over a clock", "[unit][animation]")
{
  for (const auto t : animation_clock{}.start(30s))
  {
    CHECK(true);
  }
}
