#ifndef ISAAC_ISAAC_HPP
#define ISAAC_ISAAC_HPP

#include "system/world.hpp"

#include <memory>
#include <string>
#include <string_view>

namespace isaac {
class Scene;
class World;
class Isaac
{
  World m_world{};
  std::string m_name{"Isaac Engine"};
  std::unique_ptr<Scene> m_main_scene;

 public:
  Isaac() = default;
  Isaac(std::string_view name);
  void set_scene(std::unique_ptr<Scene> scene);
  int run();

 private:
  bool start();
  void cleanup();
};
} // namespace isaac
#endif
