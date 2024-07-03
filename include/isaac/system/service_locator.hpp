#ifndef SYSTEM_SERVICE_LOCATOR_HPP
#define SYSTEM_SERVICE_LOCATOR_HPP

namespace isaac {
template<typename T>
class ServiceLocator
{
  inline static T* m_service;

 public:
  static T* get_service()
  {
    if (m_service == nullptr) {
      throw std::runtime_error("service not found");
    }
    return m_service;
  }
  static void register_service(T* service)
  {
    m_service = service;
  }
};
} // namespace isaac

#endif