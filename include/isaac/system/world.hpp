#ifndef SYSTEM_WORLD_HPP
#define SYSTEM_WORLD_HPP

#include <sfml/Graphics.hpp>

namespace isaac {
class World
{
  sf::RenderWindow m_window;

  void input();
  void update();
  void render();

 public:
  World();
  void game_loop();
};
} // namespace isaac

#endif