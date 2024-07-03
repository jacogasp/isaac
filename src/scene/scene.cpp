#include "scene/scene.hpp"

#include <utility>

namespace isaac {
std::vector<std::unique_ptr<GameObject>>& isaac::Scene::get_game_objects()
{
  return m_game_objects;
}
} // namespace isaac
