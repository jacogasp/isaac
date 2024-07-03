#include "scene/scene.hpp"

#include <utility>

namespace isaac {
void isaac::Scene::add_game_object(GameObject game_object)
{
  m_game_objects.push_back(std::move(game_object));
}
std::vector<GameObject>& isaac::Scene::get_game_objects()
{
  return m_game_objects;
}
} // namespace isaac
