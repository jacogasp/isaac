#ifndef ISAAC_GAME_HPP
#define ISAAC_GAME_HPP

#include <sfml/Graphics.hpp>

namespace isaac {
class Game
{
  sf::RenderWindow m_window;

 public:
  Game();
  int run();

 private:
  bool start();
  void input();
  void update();
  void render();
  void cleanup();
};
} // namespace isaac

#endif
