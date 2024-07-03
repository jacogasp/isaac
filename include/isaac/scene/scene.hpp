#ifndef SCENES_SCENE_HPP
#define SCENES_SCENE_HPP

#include <vector>
#include "components/game_object.hpp"

namespace isaac {
class Scene
{
  std::vector<GameObject> m_game_objects{};
  public:
   void add_game_object(GameObject game_object);
   std::vector<GameObject>& get_game_objects();
};
} // namespace isaac
#endif