#include "game.hpp"

#include "defaults.hpp"

#include <cstdlib>
#include <iostream>

#include <sfml/Window/Event.hpp>

namespace isaac {
Game::Game()
    : m_window(
          sf::VideoMode(Defaults::k_screen_width, Defaults::k_screen_height),
          Defaults::k_window_title)
{
  m_window.setFramerateLimit(Defaults::k_max_fps);
}

int Game::run()
{
  if (!start()) {
    return EXIT_FAILURE;
  }

  while (m_window.isOpen()) {
    input();
    update();
    render();
  }
  cleanup();
  return EXIT_SUCCESS;
}

bool Game::start()
{
  std::cout << "start game\n";
  return true;
}

void Game::input()
{
  sf::Event event{};
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
      return;
    }
  }
}

void Game::update()
{}

void Game::render()
{
  m_window.clear();
  m_window.display();
}

void Game::cleanup()
{}

} // namespace isaac