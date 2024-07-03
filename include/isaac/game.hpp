#ifndef ISAAC_GAME_HPP
#define ISAAC_GAME_HPP

#include "system/world.hpp"
#include <memory>

namespace isaac {
class Game
{
  std::unique_ptr<World> m_world;

 public:
  int run();

 private:
  bool start();
  void cleanup();
};
} // namespace isaac

#endif
