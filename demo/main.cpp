#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/isaac.hpp>
#include <isaac/physics/utility.hpp>
#include <isaac/scene/scene.hpp>
#include <isaac/system/input.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include <cmath>
#include <memory>
#include <utility>

class Orbiter : public isaac::GameObject
{
  isaac::GameObject* m_attractor;

 private:
  void on_start() override
  {
    auto renderer = make_component<isaac::SpriteRenderer>();
    auto shape    = renderer->make_shape<sf::CircleShape>();
    shape->setRadius(10);
    shape->setFillColor({255, 255, 255});
  }

  void on_update(float delta) override
  {
    constexpr float radius    = 100.0f;
    constexpr float frequency = 3.0f;
    static float t            = 0;
    auto position             = m_attractor->get_position();
    position.x += std::sin(t * frequency) * radius;
    position.y += std::cos(t * frequency) * radius;
    set_position(position);
    t += delta;

    if (isaac::Input::key_pressed(sf::Keyboard::Key::K)) {
      destroy();
    }
  }

  void on_destroy() override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("Orbiter destroyed!");
  }

 public:
  void set_attractor(isaac::GameObject& attractor)
  {
    m_attractor = &attractor;
  }
};

class Player : public isaac::GameObject
{
  void on_start() override
  {
    auto sprite_renderer = make_component<isaac::SpriteRenderer>();
    auto sprite          = sprite_renderer->make_shape<sf::CircleShape>();
    sprite->setRadius(25);
    sprite->setFillColor({255, 255, 255});

    auto orbiter = make_child<Orbiter>();
    orbiter->set_attractor(*this);
  }

  void on_update(float delta) override
  {
    auto position = get_position();
    auto axis     = isaac::Input::get_axis();
    auto force    = 300.0f * delta * isaac::vec3{axis.x, axis.y, 0};
    position += force;
    set_position(position);
  }
};

auto create_scene()
{
  auto scene = std::make_unique<isaac::Scene>();
  auto& root = scene->root();
  root.make_child<Player>();
  return scene;
}

int main()
{
  isaac::Isaac isaac;
  auto scene = create_scene();
  isaac.set_scene(std::move(scene));
  isaac.run();
  
  return 0;
}
