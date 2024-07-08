#ifndef INTERNAL_BASE_OBJECT_HPP
#define INTERNAL_BASE_OBJECT_HPP

#include <cstddef>

namespace isaac {
class BaseObject
{
  static std::size_t s_instance_count;
  std::size_t m_id;

 public:
  BaseObject();
  [[nodiscard]] std::size_t id() const;
};
} // namespace isaac

#endif