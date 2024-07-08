#include <isaac/isaac.hpp>
#include <isaac/scene/scene.hpp>

#include <memory>

#include "obstacle.hpp"
#include "orbiter.hpp"
#include "player.hpp"

auto create_scene()
{
  auto scene = std::make_unique<isaac::Scene>();
  auto& root = scene->root();
  root.make_child<Player>();
  root.make_child<Obstacle>();
  return scene;
}

int main()
{
  isaac::Isaac isaac;
  isaac.set_scene(create_scene());
  isaac.run();
  return 0;
}
