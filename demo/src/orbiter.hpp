#ifndef ISAAC_DEMO_ORBITER_HPP
#define ISAAC_DEMO_ORBITER_HPP

#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/system/input.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include <cmath>

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

#endif // ISAAC_DEMO_ORBITER_HPP