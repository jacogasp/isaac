#ifndef ISAAC_DEMO_PLAYER_HPP
#define ISAAC_DEMO_PLAYER_HPP

#include <isaac/components/collider_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/rigidbody_2d.hpp>
#include <isaac/components/shape_renderer.hpp>
#include <isaac/physics/collision_2d.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/input.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include "orbiter.hpp"

class Player : public isaac::GameObject
{
  isaac::RigidBody2D* m_rigid_body = nullptr;
  void on_start() override
  {
    // components
    auto shape_renderer = make_component<isaac::ShapeRenderer>();
    auto shape          = shape_renderer->make_shape<sf::CircleShape>();
    shape->setRadius(25);
    shape->setFillColor({255, 255, 255});

    m_rigid_body = make_component<isaac::RigidBody2D>();

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
    auto force    = 300.0f * delta * isaac::vec2{axis.x, axis.y};
    m_rigid_body->set_velocity(force);
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
