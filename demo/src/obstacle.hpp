#ifndef ISAAC_DEMO_OBSTACLE_HPP
#define ISAAC_DEMO_OBSTACLE_HPP

#include <isaac/components/collision_object_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/shape_renderer.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include <LinearMath/btVector3.h>

class Obstacle : public isaac::GameObject
{
  void on_start() override
  {
    set_position({300, 500, 0});
    isaac::vec2 size{200, 25};
    isaac::Box2DShape box{{size.x, size.y, 10000}};
    auto collider = make_component<isaac::CollisionObject2D>(box);
    auto renderer = make_component<isaac::ShapeRenderer>();
    auto shape    = renderer->make_shape<sf::RectangleShape>();
    shape->setSize({size.x, size.y});
  }

  void on_destroy() override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("Obstacle destroyed!");
  }
};
#endif // ISAAC_DEMO_OBSTACLE_HPP
