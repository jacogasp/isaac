#ifndef ISAAC_GAME_HPP
#define ISAAC_GAME_HPP

#include "system/world.hpp"

namespace isaac {
class Game
{
  World m_world{};

 public:
  int run();

 private:
  bool start();
  void cleanup();
};
} // namespace isaac

#endif
