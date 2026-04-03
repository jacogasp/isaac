#include "isaac/components/component.hpp"
#include "isaac/components/game_object.hpp"

namespace isaac {
GameObject* Component::game_object()
{
  return m_parent;
}
} // namespace isaac
