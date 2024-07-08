#include "internal/base_object.hpp"

namespace isaac {

std::size_t BaseObject::s_instance_count{0};

BaseObject::BaseObject()
{
  m_id = s_instance_count++;
}

std::size_t isaac::BaseObject::id() const
{
  return m_id;
}
} // namespace isaac
