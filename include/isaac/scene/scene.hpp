#ifndef SCENES_SCENE_HPP
#define SCENES_SCENE_HPP

#include "components/game_object.hpp"
#include <memory>

namespace isaac {
class Scene
{
  GameObject m_root{};

 public:
  GameObject& root();
};
} // namespace isaac
#endif
