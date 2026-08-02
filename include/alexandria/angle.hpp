#ifndef ALEXANDRIA_ANGLE_HPP
#define ALEXANDRIA_ANGLE_HPP

#include <numbers>
#include <ratio>

namespace alexandria
{
  template <class Rep, class Period = std::ratio<1>>
  class angle final
  {
  public:
    using rep = Rep;
    using period = Period;

  private:
    rep m_angle{0};

  public:
    /// @brief Construct the angle 0.
    constexpr angle() = default;

    /// @brief Copy an angle.
    constexpr angle(const angle &) = default;

    /// @brief Move an angle.
    angle(angle &&) = default;

    // template <class Rep2>
    // constexpr explicit angle(const Rep2 &);
    // template <class Rep2, class Period2>
    // constexpr angle(const angle<Rep2, Period2> &);

    /// @brief Copy-assign an angle.
    angle &operator=(const angle &) = default;

    /**
     * @brief Get the raw angle value.
     * @return The raw angle value.
     */
    [[nodiscard]] constexpr rep count() const noexcept { return m_angle; }

    // Do I really need these?
    // static constexpr angle min() noexcept;
    // static constexpr angle max() noexcept;

    /**
     * @brief Unary +
     * @return A copy of *this.
     */
    [[nodiscard]] constexpr angle operator+() const noexcept
    {
      return *this;
    };

    /**
     * @brief Unary -
     * @return The negative of *this.
     */
    [[nodiscard]] constexpr angle operator-() const noexcept
    {
      return angle{-m_angle};
    }

    // Increment and decrement
    // Why aren't these noexcept?
    // constexpr angle &operator++();
    // constexpr angle &operator++(int);
    // constexpr angle &operator--();
    // constexpr angle &operator--(int);

    // Compound assignment
    // Why aren't these noexcept?
    // constexpr angle &operator+=(const angle &);
    // constexpr angle &operator-=(const angle &);
    // constexpr angle &operator*=(const rep &);
    // constexpr angle &operator/=(const rep &);
    // constexpr angle &operator%=(const rep &);
    // constexpr angle &operator%=(const angle &);
  };

  // Arithmetic operators
  // Why aren't these noexcept and [[nodiscard]]?
  template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  constexpr std::common_type_t<angle<Rep1, Period1>, angle<Rep2, Period2>>
  operator+(const angle<Rep1, Period1> &, const angle<Rep2, Period2> &);

  template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  constexpr std::common_type_t<angle<Rep1, Period1>, angle<Rep2, Period2>>
  operator-(const angle<Rep1, Period1> &, const angle<Rep2, Period2> &);

  template <typename Rep1, typename Period, typename Rep2>
  constexpr angle<std::common_type_t<Rep1, Rep2>, Period>
  operator*(const angle<Rep1, Period> &, const Rep2 &);

  template <typename Rep1, typename Rep2, typename Period>
  constexpr angle<std::common_type_t<Rep1, Rep2>, Period>
  operator*(const Rep1 &, const angle<Rep2, Period> &);

  template <typename Rep1, typename Period, typename Rep2>
  constexpr angle<std::common_type_t<Rep1, Rep2>, Period>
  operator/(const angle<Rep1, Period> &, const Rep2 &);

  template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  constexpr std::common_type_t<angle<Rep1, Period1>, angle<Rep2, Period2>>
  operator/(const angle<Rep1, Period1> &, const angle<Rep2, Period2> &);

  template <typename Rep1, typename Period, typename Rep2>
  constexpr angle<std::common_type_t<Rep1, Rep2>, Period>
  operator%(const angle<Rep1, Period> &, const Rep2 &);

  template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  constexpr std::common_type_t<angle<Rep1, Period1>, angle<Rep2, Period2>>
  operator%(const angle<Rep1, Period1> &, const angle<Rep2, Period2> &);

  // Comparison
  // template <typename Rep1, typename Period1, typename Rep2, typename Period2>
  // requires std::three_way_comparable<std::common_type_t<Rep1, Rep2>>
  // constexpr auto operator<=>(const angle<Rep1, Period1> &, const angle<Rep2, Period2> &);

  // Angle cast
  // Is this really necessary? Doesn't the constructor do this?
  // angle_cast
  // floor
  // ceil
  // abs

  // Stream insertion
  // TODO Implement formatting, so (for example) s << arcseconds may format as
  // dd:mm:ss.
  // operator<<
  // from_stream

  // Type aliases
  using milliarcseconds = angle<int64_t, std::milli>;
  using arcseconds = angle<int64_t>;
  using arcminutes = angle<int32_t, std::ratio<60, 1>>;
  using degrees = angle<int32_t, std::ratio<3600, 1>>;
  using hours = angle<int32_t, std::ratio<54'000, 1>>;
  using radians = angle<double, std::ratio<std::numbers::pi, 180 * 60 * 60>>;

  namespace literals
  {
    constexpr milliarcseconds operator""_ms(unsigned long long a) noexcept;
    constexpr arcseconds operator""_s(unsigned long long a) noexcept;
    constexpr arcminutes operator""_m(unsigned long long a) noexcept;
    constexpr degrees operator""_d(unsigned long long a) noexcept;
    constexpr hours operator""_h(unsigned long long a) noexcept;
  }
}

#endif
