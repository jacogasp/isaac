#include "scene/scene_manager.hpp"

namespace isaac {
void SceneManager::create_default_scene()
{
  m_current_scene = std::make_unique<Scene>();
}

Scene* SceneManager::get_current_scene()
{
  return m_current_scene.get();
}
} // namespace isaac
