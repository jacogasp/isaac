#include <isaac/isaac.hpp>
#include <isaac/scene/scene.hpp>

#include <memory>

#include "hud.hpp"
#include "obstacle.hpp"
#include "player.hpp"

auto create_scene()
{
  auto scene = std::make_unique<isaac::Scene>();
  auto& root = scene->root();
  root.make_child<Player>();
  root.make_child<Obstacle>();
  root.make_child<Hud>();
  return scene;
}

int main()
{
  isaac::Isaac isaac{{800, 600}, "Isaac Demo"};
  isaac.set_scene(create_scene());
  isaac.run();
  return 0;
}
