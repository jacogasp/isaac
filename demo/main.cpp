#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/game.hpp>
#include <isaac/scene/scene.hpp>

#include <memory>
#include <utility>

auto create_scene()
{
  isaac::GameObject go;
  auto scene           = std::make_unique<isaac::Scene>();
  auto sprite_renderer = go.make_component<isaac::SpriteRenderer>();
  auto shape           = sprite_renderer->make_shape<sf::CircleShape>();
  shape->setRadius(50);
  shape->setFillColor({255, 255, 255});
  scene->add_game_object(std::move(go));
  return scene;
}

int main()
{
  isaac::Game game;
  auto scene = create_scene();
  game.set_scene(std::move(scene));
  game.run();
  return 0;
}