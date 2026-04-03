#ifndef ISAAC_SCENES_SCENE_HPP
#define ISAAC_SCENES_SCENE_HPP

#include "isaac/components/game_object.hpp"

namespace isaac {
class Scene
{
  GameObject m_root{};

 public:
  GameObject& root();
};
} // namespace isaac
#endif
