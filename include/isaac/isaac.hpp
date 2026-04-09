#ifndef ISAAC_ISAAC_HPP
#define ISAAC_ISAAC_HPP

#include "isaac/physics/physics_2d.hpp"
#include "isaac/render/window_server.hpp"
#include "isaac/scene/scene_manager.hpp"
#include "isaac/system/input.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/world.hpp"

#include <SFML/System/Vector2.hpp>

#include <memory>
#include <string>

namespace isaac {

class Scene;
class SceneManager;
class PhysicsServer2D;

class Isaac
{
  std::unique_ptr<Logger> m_logger;
  std::unique_ptr<WindowServer> m_window_server;
  std::unique_ptr<PhysicsServer2D> m_physics_server;
  std::unique_ptr<SceneManager> m_scene_manager;
  std::unique_ptr<Input> m_input;
  World m_world;

  std::unique_ptr<Scene> m_main_scene;

 public:
  Isaac(std::string name, sf::Vector2u window_size,
        Logger::Level = Logger::Level::INFO);
  ~Isaac();

  void set_scene(std::unique_ptr<Scene> scene);
  int run();

 private:
  bool start();
};
} // namespace isaac
#endif
