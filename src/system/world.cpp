#include "system/world.hpp"
#include "system/defaults.hpp"

namespace isaac {
World::World()
    : m_window(
          sf::VideoMode(Defaults::k_screen_width, Defaults::k_screen_height),
          Defaults::k_window_title)
{
  m_window.setFramerateLimit(Defaults::k_max_fps);
}

void World::input()
{
  sf::Event event{};
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
      return;
    }
  }
}

void World::update()
{}

void World::render()
{
  m_window.clear();
  m_window.display();
}

void World::game_loop()
{
  while (m_window.isOpen()) {
    input();
    update();
    render();
  }
}
} // namespace isaac