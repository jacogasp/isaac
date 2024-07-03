#ifndef SYSTEM_SERVICE_LOCATOR_HPP
#define SYSTEM_SERVICE_LOCATOR_HPP

#include <format>
#include <memory>
#include <stdexcept>
#include <string>

namespace isaac {
template<typename T>
class ServiceLocator
{
  inline static std::unique_ptr<T> m_service;

 public:
  static T* get_service()
  {
    if (m_service == nullptr) {
      auto msg = std::format("service '{}' not found", typeid(T).name());
      throw std::runtime_error(msg);
    }
    return m_service.get();
  }

  template<typename... Args>
  static T* register_service(Args... args)
  {
    m_service = std::make_unique<T>(args...);
    return m_service.get();
  }

  static void release()
  {
    m_service.release();
  }
};
} // namespace isaac

#endif