#include "isaac/isaac.hpp"

#include "isaac/physics/physics_2d.hpp"
#include "isaac/render/window_server.hpp"
#include "isaac/scene/scene_manager.hpp"
#include "isaac/system/input.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/service_locator.hpp"

#include <cstdlib>
#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <sfml/Window/Event.hpp>

namespace isaac {

Isaac::Isaac(std::string name, sf::Vector2u window_size, Logger::Level level)
    : m_logger{*ServiceLocator<Logger>::register_service(level)}
    , m_window_server{window_size, std::move(name)}
    , m_physics_server{*ServiceLocator<PhysicsServer2D>::register_service()}
    , m_scene_manager{}
    , m_world{m_window_server, m_scene_manager, m_physics_server}
{
  ServiceLocator<Input>::register_service();
}

Isaac::~Isaac()
{
  m_logger.info("Closing Isaac game");
}

void Isaac::set_scene(std::unique_ptr<Scene> scene)
{
  m_main_scene = std::move(scene);
}

int Isaac::run()
{
  if (!start()) {
    return EXIT_FAILURE;
  }
  // here everything happens
  m_world.game_loop();
  return EXIT_SUCCESS;
}

bool Isaac::start()
{
  try {
    if (m_main_scene == nullptr) {
      throw std::runtime_error(
          "cannot found any scene to display. Please load a scene with "
          "Isaac::add_scene before starting the game");
    }
    m_scene_manager.set_scene(std::move(m_main_scene));
    m_world.start();
    m_logger.info("Game started");
  } catch (std::exception& e) {
    std::cerr << "cannot initialize game engine because of an error "
              << e.what() << '\n';
    return false;
  }
  return true;
}
} // namespace isaac
