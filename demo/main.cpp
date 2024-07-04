#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/game.hpp>
#include <isaac/scene/scene.hpp>
#include <isaac/system/input.hpp>

#include <memory>
#include <utility>

class Player : public isaac::GameObject
{
  sf::CircleShape* m_shape;

  void on_start() override
  {
    auto sprite_renderer = make_component<isaac::SpriteRenderer>();
    m_shape              = sprite_renderer->make_shape<sf::CircleShape>();
    m_shape->setRadius(50);
    m_shape->setFillColor({255, 255, 255});
  }

  void on_update(float delta) override
  {
    auto position = m_shape->getPosition();
    auto axis     = isaac::Input::get_axis();
    auto force    = 300.0f * axis * delta;
    m_shape->setPosition(position + sf::Vector2f{force.x, force.y});
  }
};

auto create_scene()
{
  auto scene = std::make_unique<isaac::Scene>();
  scene->make_game_object<Player>();
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
