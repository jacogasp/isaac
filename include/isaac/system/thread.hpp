#ifndef SYSTEM_THREAD_HPP
#define SYSTEM_THREAD_HPP

#include <thread>

namespace isaac {

template<typename... Args>
class thread_guard
{
  std::thread m_t;

 public:
  explicit thread_guard(Args... args)
      : m_t{args...} {};
  ~thread_guard()
  {
    join();
  }
  void join()
  {
    if (m_t.joinable())
      m_t.join();
  }
};

} // namespace isaac
#endif
