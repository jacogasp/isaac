#include "scene/scene_manager.hpp"
#include <utility>

namespace isaac {
void SceneManager::create_default_scene()
{
  m_current_scene = std::make_unique<Scene>();
}

void SceneManager::set_scene(std::unique_ptr<Scene> scene)
{
  m_current_scene = std::move(scene);
}

Scene* SceneManager::get_current_scene()
{
  return m_current_scene.get();
}
} // namespace isaac
