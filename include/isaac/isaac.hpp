#ifndef ISAAC_ISAAC_HPP
#define ISAAC_ISAAC_HPP

#include "system/world.hpp"

#include <SFML/System/Vector2.hpp>

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
  sf::Vector2u m_window_size;
  std::unique_ptr<Scene> m_main_scene;

 public:
  Isaac(sf::Vector2u window_size, std::string_view name);
  void set_scene(std::unique_ptr<Scene> scene);
  int run();

 private:
  bool start();
  void cleanup();
};
} // namespace isaac
#endif
