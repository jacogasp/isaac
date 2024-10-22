#include "isaac.hpp"

#include "physics/physics_2d.hpp"
#include "render/window_server.hpp"
#include "scene/scene_manager.hpp"
#include "system/input.hpp"
#include "system/logger.hpp"
#include "system/service_locator.hpp"

#include <cstdlib>
#include <iostream>

#include <sfml/Window/Event.hpp>

namespace isaac {

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
  cleanup();
  return EXIT_SUCCESS;
}

bool Isaac::start()
{
  try {
    ServiceLocator<Logger>::register_service(Logger::Level::DEBUG);
    ServiceLocator<WindowServer>::register_service();
    ServiceLocator<Input>::register_service();
    ServiceLocator<SceneManager>::register_service();
    ServiceLocator<PhysicsServer2D>::register_service();

    if (m_main_scene == nullptr) {
      throw std::runtime_error(
          "cannot found any scene to display. Please load a scene with "
          "Isaac::add_scene before starting the game");
    }

    auto scene_manager = ServiceLocator<SceneManager>::get_service();
    scene_manager->set_scene(std::move(m_main_scene));
    m_world.start();

    auto logger = ServiceLocator<Logger>::get_service();
    logger->debug("game started");
  } catch (std::exception& e) {
    std::cerr << "cannot initialize game engine because of an error "
              << e.what() << '\n';
    return false;
  }
  return true;
}

void Isaac::cleanup()
{
  m_world.clear();
  // for some reasons, we have to forcefully release the window server because
  // sf::RenderWindow crashes during at destructor otherwise
  ServiceLocator<WindowServer>::release();
  auto logger = ServiceLocator<Logger>::get_service();
  logger->debug("closing game");
}
} // namespace isaac
