#ifndef SYSTEM_WORLD_HPP
#define SYSTEM_WORLD_HPP

#include "render/window_server.hpp"
#include "scene/scene_manager.hpp"

namespace isaac {
class World
{
  sf::RenderWindow* m_window;
  SceneManager* m_scene_manager;

  void input();
  void update();
  void render();

 public:
  World();
  void game_loop();
};
} // namespace isaac

#endif