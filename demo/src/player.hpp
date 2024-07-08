#ifndef ISAAC_DEMO_PLAYER_HPP
#define ISAAC_DEMO_PLAYER_HPP

#include <isaac/components/collider_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/physics/collision_2d.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/input.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include "orbiter.hpp"

class Player : public isaac::GameObject
{
  void on_start() override
  {
    // components
    auto sprite_renderer = make_component<isaac::SpriteRenderer>();
    auto sprite          = sprite_renderer->make_shape<sf::CircleShape>();
    sprite->setRadius(25);
    sprite->setFillColor({255, 255, 255});

    auto collider = make_component<isaac::Collider2D>();
    isaac::CollisionShape2D collision_shape{};
    isaac::Circle2D circle_shape{};
    circle_shape.radius = 25;
    collision_shape.add_shape(circle_shape);
    collider->set_collision_shape(collision_shape);

    // children
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

  void on_collision_2d(isaac::Collision2D const& collision) override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("There was a collision!");
    if (collision.other->game_object()) {
      collision.other->game_object()->destroy();
    }
  }
};

#endif // ISAAC_DEMO_PLAYER_HPP