#ifndef ISAAC_SYSTEM_WORLD_HPP
#define ISAAC_SYSTEM_WORLD_HPP

#include "isaac/render/window_server.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/observer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace isaac {

class SceneManager;
class PhysicsServer2D;

class World : public Observable<sf::Event>
{
  sf::Clock m_frame_clock{};
  sf::Time m_frame_time{};
  SceneManager& m_scene_manager;
  sf::RenderWindow& m_window;
  PhysicsServer2D& m_physics_server_2d;
  Logger& m_logger;

  void input();
  void update();
  void render();
  void destroy_queued();

 public:
  World(WindowServer& window_server, SceneManager& scene_manager,
        PhysicsServer2D& physics_server);
  ~World();
  void start();
  void game_loop();
  void clear();
};
} // namespace isaac
#endif
