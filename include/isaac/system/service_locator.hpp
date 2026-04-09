#ifndef SYSTEM_SERVICE_LOCATOR_HPP
#define SYSTEM_SERVICE_LOCATOR_HPP

#include <format>
#include <memory>
#include <stdexcept>

namespace isaac {
template<typename T>
class ServiceLocator
{
  inline static T* m_service;

 public:
  static T* get_service()
  {
    if (m_service == nullptr) {
      auto msg = std::format("service '{}' not found", typeid(T).name());
      throw std::runtime_error(msg);
    }
    return m_service;
  }

  template<typename... Args>
  static std::unique_ptr<T> register_service(Args... args)
  {
    auto service = std::make_unique<T>(args...);
    m_service    = service.get();
    return service;
  }
};
} // namespace isaac
#endif
