#ifndef SYSTEM_WORLD_HPP
#define SYSTEM_WORLD_HPP

#include "render/window_server.hpp"
#include "scene/scene_manager.hpp"
#include "system/observer.hpp"
#include "physics/physics_2d.hpp"

#include <SFML/System/Clock.hpp>

namespace isaac {
class World : public Observable<sf::Event>
{
  sf::Clock m_frame_clock{};
  sf::RenderWindow* m_window;
  SceneManager* m_scene_manager;
  PhysicsServer2D* m_physics_server_2d;

  void input();
  void update();
  void render();
  void destroy_queued();

 public:
  void start();
  void game_loop();
  void clear();
};
} // namespace isaac
#endif
