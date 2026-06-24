#ifndef ALEXANDRIA_THREAD_SAFE_HPP
#define ALEXANDRIA_THREAD_SAFE_HPP

namespace alex {
template <typename T, typename Mutex = std::mutex, typename Lock = std::scoped_lock>
class thread_safe {
public:
  using value_type = T;
  using mutex_type = Mutex;
  using lock_type = Lock;

private:
  value_type m_value;
  mutex_type m_mutex;

public:
  explicit thread_safe(value_type value): m_value{std::move(value)} {}
  explicit thread_safe(value_type&& value): m_value{value} {}
  template <typename... Args>
  explicit thread_safe(Args... args): m_value(std::forward<Args...>(args)) {}

  ~thread_safe() {
    // Need to lock the mutex to safely destruct the
    // protected value. Then, ensure the protected
    // value is destructed before the lock destructs
    // and releases the mutex.
    lock_type lock{m_mutex};
    m_value.~value_type();
  }

  // TODO Implement these; they need careful handling
  // of the mutex, self-assignment, etc.
  thread_safe(const thread_safe&) = delete;
  thread_safe(thread_safe&&) = delete;
  thread_safe& operator=(const thread_safe&) = delete;
  thread_safe& operator=(const value_type&) = delete;
  thread_safe& operator=(thread_safe&&) = delete;
  thread_safe& operator=(value_type&&) = delete;

  [[nodiscard]] value_type value() const {
    Lock lock{m_mutex};
    return m_value;
  }

  template <typename F>
  auto execute(F f) {
    // TODO handle when `f` is a member function
    // of value_type.
    Lock lock{m_mutex};
    return f(m_value);
  }

  template <typename F, typename Args...>
  auto execute(F f, Args... args) {
    // TODO Handle when `f` is a member function
    // of value_type.
    Lock lock{m_mutex};
    return f(m_value, std::forward<Args...>(args));
  }
};
} // namespace alex

#endif
