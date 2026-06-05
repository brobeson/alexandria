#ifndef ALEXANDRIA_RANGE_HPP
#define ALEXANDRIA_RANGE_HPP

#include <stdexcept>
#include <type_traits>

namespace alex
{
  template <typename T>
  class range final
  {
  public:
    using value_type = std::remove_cvref_t<T>;

  private:
    value_type m_minimum;
    value_type m_maximum;

  public:
    /**
     * \brief Construct a range object.
     * \param[in] min,max The bounds of the range. \a min must be less than
     * \a max.
     * \throw std::invalid_argument if \$ max \le min \$
     */
    constexpr range(value_type min, value_type max)
        : m_minimum{std::move(min)}, m_maximum{std::move(max)}
    {
      if (m_maximum <= m_minimum)
      {
        throw std::invalid_argument{"alex::range minimum must be less than maximum"};
      }
    }

    constexpr range(const range &) = default;
    constexpr range(range &&) = default;
    ~range() = default;

    constexpr range &operator=(const range &) = default;
    constexpr range &operator=(range &&) = default;

    /// \return the minimum bound of the range
    [[nodiscard]] constexpr auto minimum() const noexcept { return m_minimum; }

    /// \return the maximum bound of the range
    [[nodiscard]] constexpr auto maximum() const noexcept { return m_maximum; }

    /// \return \$ maximum() - minimum() \$
    [[nodiscard]] constexpr auto distance() const noexcept
    {
      return m_maximum - m_minimum;
    }

    /**
     * \brief Check if the range contains a specific value.
     * \param[in] v Check if this value is within the range.
     * \retval true \$ minimum() \le v \le maximum() \$
     * \retval false \$ v \lt minimum() \$ or \$ maximum() \lt v \$
     */
    [[nodiscard]] constexpr auto contains(const value_type &v) const noexcept
    {
      return m_minimum <= v && v <= m_maximum;
    }

    /**
     * \brief Calculate the value
     *
     * \tparam Float
     * \param[in] a
     * \return
     */
    template <typename Float = float>
    [[nodiscard]] constexpr auto linear_interpolate(Float a) const noexcept
    {
      a = std::min(1.0, std::max(0.0, a));
      return m_minimum + a * distance();
    }

    template <typename Float = float>
    [[nodiscard]] constexpr auto smooth_interpolate(Float a) const noexcept
    {
      const auto x{linear_interpolate(a)};
      return x * x * (3 - 2 * x);
    }

    template <typename Float = float>
    [[nodiscard]] constexpr auto normalized_percent(value_type v) const noexcept
    {
      return static_cast<Float>(m_maximum - v) / distance();
    }

    template <typename Float = float>
    [[nodiscard]] constexpr auto percent(value_type v) const noexcept
    {
      return normalized_percent(v) * 100;
    }
  };
} // namespace alex

#endif
