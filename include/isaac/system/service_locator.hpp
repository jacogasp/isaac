#ifndef SYSTEM_SERVICE_LOCATOR_HPP
#define SYSTEM_SERVICE_LOCATOR_HPP

#include <memory>
#include <stdexcept>

namespace isaac {
template<typename T>
class ServiceLocator
{
  inline static std::unique_ptr<T> m_service;

 public:
  static T* get_service()
  {
    if (m_service == nullptr) {
      throw std::runtime_error("service not found");
    }
    return m_service.get();
  }

  template<typename... Args>
  static void register_service(Args... args)
  {
    m_service = std::make_unique<T>(args...);
  }

  static void release()
  {
    m_service.release();
  }
};
} // namespace isaac

#endif