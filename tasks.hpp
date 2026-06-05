#ifndef ALEXANDRIA_TASKS_HPP
#define ALEXANDRIA_TASKS_HPP

namespace alex
{
  template <typename Callable>
  class task
  {
  private:
    callable m_task_function;

  public:
    using callable = Callable;
    task(callable f) : m_task_function{f} {}
  };

}

#endif
