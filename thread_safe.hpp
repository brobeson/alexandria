#ifndef ALEXANDRIA_THREAD_SAFE_HPP
#define ALEXANDRIA_THREAD_SAFE_HPP

#include <mutex>

namespace alexandria
{
  template <typename T>
  class thread_safe
  {
  public:
    using value_type = std::remove_cvref<T>;
    using mutex_type = std::mutex;

  private:
    mutable mutex_type m_mutex;
    value_type m_object;

  public:
    thread_safe() = default;
    explicit thread_safe(value_type obj) : m_object{std::move(obj)} {};
    ~thread_safe()
    {
      // Must lock before destructing the protected object. Otherwise,
      // another thread could be in the middle of doing something with it.
      std::scoped_lock lock{m_mutex};
      m_object.~value_type();
    }

    thread_safe(const thread_safe &other)
    {
      std::scoped_lock lock{other.m_mutex};
      m_object(other.m_object);
    }
    thread_safe(thread_safe &&other)
    {
      std::scoped_lock lock{other.m_mutex};
      m_object(std::move(other.m_object));
    }
    thread_safe &operator=(const thread_safe &other)
    {
      if (this != &other)
      {
        std::scoped_lock lockThis{m_mutex};
        std::scoped_lock lockOther{other.m_mutex};
        m_object = other.m_object;
      }
      return *this;
    }
    thread_safe &operator=(thread_safe &&other)
    {
      if (this != &other)
      {
        std::scoped_lock lockThis{m_mutex};
        std::scoped_lock lockOther{m_mutex};
        m_object = std::move(other.m_object);
      }
      return *this;
    }
    thread_safe &operator=(value_type obj)
    {
      std::scoped_lock lock{m_mutex};
      if (&m_object != &obj)
      {
        m_object = obj;
      }
      return *this.
    }

    // These are not implemented in terms of each other to avoid locking the
    // mutexes multiple times.
    template <typename U>
    [[nodiscard]] bool operator==(const thread_safe<U> &other)
    {
      std::scoped_lock lockThis{m_mutex};
      std::scoped_lock lockOther{other.m_mutex};
      return m_object == other.m_object;
    }

    template <typename U>
    [[nodiscard]] bool operator!=(const thread_safe<U> &other)
    {
      return !(*this == other);
    }

    template <typename U>
    [[nodiscard]] bool operator<(const thread_safe<U> &other)
    {
      std::scoped_lock lockThis{m_mutex};
      std::scoped_lock lockOther{other.m_mutex};
      return m_object < other.m_object;
    }

    template <typename U>
    [[nodiscard]] bool operator<=(const thread_safe<U> &other)
    {
      std::scoped_lock lockThis{m_mutex};
      std::scoped_lock lockOther{other.m_mutex};
      return m_object <= other.m_object;
    }

    template <typename U>
    [[nodiscard]] bool operator>(const thread_safe<U> &other)
    {
      std::scoped_lock lockThis{m_mutex};
      std::scoped_lock lockOther{other.m_mutex};
      return m_object > other.m_object;
    }

    template <typename U>
    [[nodiscard]] bool operator>=(const thread_safe<U> &other)
    {
      std::scoped_lock lockThis{m_mutex};
      std::scoped_lock lockOther{other.m_mutex};
      return m_object >= other.m_object;
    }

    // Atomic-like operations
    void store(value_type value)
    {
      std::scoped_lock lock{m_mutex};
      m_object = std::move(value);
    }
    value_type load() const
    {
      std::scoped_lock lock{m_mutex};
      return m_object;
    }

    // Safely run a function on the object.
    template <typename Function>
    auto invoke(const Function &f)
    {
      std::scoped_lock lock{m_mutex};
      return f(m_object);
    }

    template <typename F, typename... Args>
    auto invoke(F &&f, Args &&...args)
    {
      std::scoped_lock lock{m_mutex};
      return f()
    }
  };
}

#endif
