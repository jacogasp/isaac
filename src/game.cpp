#include "game.hpp"

#include "scene/scene_manager.hpp"
#include "system/logger.hpp"
#include "system/service_locator.hpp"

#include <cstdlib>
#include <iostream>

#include <sfml/Window/Event.hpp>

namespace isaac {
bool Game::start()
{
  try {
    ServiceLocator<Logger>::register_service(Logger::Level::DEBUG);
    ServiceLocator<SceneManager>::register_service();
  } catch (std::exception& e) {
    std::cerr << "cannot initialize game engine because of an error "
              << e.what() << '\n';
    return false;
  }

  auto logger = ServiceLocator<Logger>::get_service();
  logger->debug("game started");
  return true;
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

void Game::cleanup()
{
  auto logger = ServiceLocator<Logger>::get_service();
  logger->debug("closing game");
}

} // namespace isaac