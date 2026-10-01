#ifndef ALEXANDRIA_RANGE_HPP
#define ALEXANDRIA_RANGE_HPP

namespace alex
{
  template <typename T>
  struct range final
  {
    using value_type = std::remove_cvref_t<T>;
    const value_type start;
    const value_type end;
    const value_type step{1};
  };

  namespace detail
  {
    template <typename T>
    class range_iterator
    {
    public:
      using value_type = range<T>::value_type;

    private:
      value_type start;
      value_type end;
      value_type step;
      value_type next{start};
      bool at_end{false};

      friend end(range<T> &);

    public:
      // bug If T is unsigned, negating `step` will cause a problem.
      explicit range_iterator(const range<T> &r) : start{r.start}, end{r.end}, step{start <= end ? r.step : -r.step} {}

      auto &operator++(int)
      {
        next += step;
        at_end = next >= end;
        return *this;
      }

      auto operator*()
      {
        return next;
      }

      auto operator==(const range_iterator &other)
      {
        return at_end && other.at_end;
      }
    };
  }

  auto begin(range &r)
  {
    return detail::range_iterator{r};
  }

  auto end(range &r)
  {
    detail::range_iterator i{r};
    r.at_end = true;
    return r;
  }
}

#endif