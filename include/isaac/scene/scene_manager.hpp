#ifndef SCENE_SCENE_MANAGER_HPP
#define SCENE_SCENE_MANAGER_HPP

#include "scene/scene.hpp"

#include <memory>

namespace isaac {
class SceneManager
{
  std::unique_ptr<Scene> m_current_scene;

 public:
  void create_default_scene();
  void set_scene(std::unique_ptr<Scene> scene);
  Scene* get_current_scene();
};
} // namespace isaac
#endif
