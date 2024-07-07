#include "internal/base_object.hpp"

namespace isaac {

std::size_t BaseObject::s_instance_count{0};

BaseObject::BaseObject()
{
  ++s_instance_count;
}

std::size_t isaac::BaseObject::id() const
{
  return BaseObject::s_instance_count;
}
} // namespace isaac
