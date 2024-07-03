#include "game.hpp"

#include "render/window_server.hpp"
#include "scene/scene_manager.hpp"
#include "system/logger.hpp"
#include "system/service_locator.hpp"

#include <cstdlib>
#include <iostream>

#include <sfml/Window/Event.hpp>

namespace isaac {

void Game::set_scene(std::unique_ptr<Scene> scene)
{
  m_main_scene = std::move(scene);
}

int Game::run()
{
  if (!start()) {
    return EXIT_FAILURE;
  }
  // here everything happens
  m_world.game_loop();
  cleanup();
  return EXIT_SUCCESS;
}

bool Game::start()
{
  try {
    auto logger =
        ServiceLocator<Logger>::register_service(Logger::Level::DEBUG);
    ServiceLocator<WindowServer>::register_service();

    auto scene_manager = ServiceLocator<SceneManager>::register_service();
    if (m_main_scene == nullptr) {
      throw std::runtime_error(
          "cannot found any scene to display. Please load a scene with "
          "Game::add_scene before starting the game");
    }
    scene_manager->set_scene(std::move(m_main_scene));
    m_world.init();
    logger->debug("game started");
  } catch (std::exception& e) {
    std::cerr << "cannot initialize game engine because of an error "
              << e.what() << '\n';
    return false;
  }
  return true;
}

void Game::cleanup()
{
  // for some reasons, we have to forcefully release the window server because
  // sf::RenderWindow crashes during at destructor otherwise
  ServiceLocator<WindowServer>::release();
  auto logger = ServiceLocator<Logger>::get_service();
  logger->debug("closing game");
}
} // namespace isaac
