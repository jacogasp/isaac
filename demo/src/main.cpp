#include <isaac/isaac.hpp>
#include <isaac/scene/scene.hpp>

#include <memory>

#include "hud.hpp"
#include "obstacles.hpp"
#include "player.hpp"
#include "spawner.hpp"
#include "walls.hpp"

class MainScene : public isaac::Scene
{
 public:
  MainScene()
  {
    auto& root = this->root();
    // root.make_child<Player>();
    root.make_child<Walls>();
    root.make_child<Obstacles>();
    auto& hud     = root.make_child<Hud>();
    auto& spawner = root.make_child<Spawner>();
    spawner.add_observer(hud);
    hud.add_observer(spawner);
  }
};

int main()
{
  isaac::Isaac isaac{"Isaac Demo", {800, 600}, isaac::Logger::Level::DEBUG};
  isaac.set_scene(std::make_unique<MainScene>());
  isaac.run();
  return 0;
}
