#ifndef ISAAC_DEMO_OBSTACLE_HPP
#define ISAAC_DEMO_OBSTACLE_HPP

#include <isaac/components/collider_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/sprite_renderer.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

class Obstacle : public isaac::GameObject
{
  void on_start() override
  {
    set_position({300, 300, 0});
    isaac::CollisionShape2D collision_shape;
    isaac::Rectangle2D rectangle{{0, 0}, {20, 50}};
    collision_shape.add_shape(rectangle);
    auto collider = make_component<isaac::Collider2D>();
    collider->set_collision_shape(collision_shape);

    auto renderer = make_component<isaac::SpriteRenderer>();
    auto sprite   = renderer->make_shape<sf::RectangleShape>();
    sprite->setSize({20, 50});
  }

  void on_destroy() override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("Obstacle destroyed!");
  }
};
#endif // ISAAC_DEMO_OBSTACLE_HPP