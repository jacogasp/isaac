#ifndef SCENES_SCENE_HPP
#define SCENES_SCENE_HPP

#include "components/game_object.hpp"
#include <memory>
#include <vector>

namespace isaac {
class Scene
{
  std::vector<std::unique_ptr<GameObject>> m_game_objects{};

 public:
  template<typename T>
  void make_game_object();
  std::vector<std::unique_ptr<GameObject>>& get_game_objects();
};

template<typename T>
void isaac::Scene::make_game_object()
{
  m_game_objects.emplace_back(std::make_unique<T>());
}
} // namespace isaac
#endif