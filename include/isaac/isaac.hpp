#ifndef ISAAC_ISAAC_HPP
#define ISAAC_ISAAC_HPP

#include "system/world.hpp"
#include <memory>

namespace isaac {
class Scene;
class World;
class Isaac
{
  World m_world{};
  std::unique_ptr<Scene> m_main_scene;

 public:
  void set_scene(std::unique_ptr<Scene> scene);
  int run();

 private:
  bool start();
  void cleanup();
};
} // namespace isaac
#endif
