#ifndef ISAAC_DEMO_OBSTACLES_HPP
#define ISAAC_DEMO_OBSTACLES_HPP

#include "isaac/components/collision_object_2d.hpp"
#include "isaac/components/shape_renderer.hpp"
#include "isaac/physics/collision_shape_2d.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <isaac/components/game_object.hpp>

class Obstacle : public isaac::GameObject
{
  void on_start() override
  {
    make_component<isaac::CollisionObject2D>(isaac::Box2DShape{{15, 15}});
    auto sr = make_component<isaac::ShapeRenderer>();
    sr->make_shape<sf::RectangleShape>(sf::Vector2f{15, 15});
  }
};

class Obstacles : public isaac::GameObject
{
  void on_start() override
  {
    auto const size = 75.f;
    for (int i = 1; i <= 8; ++i) {
      for (int j = 0; j < i; ++j) {
        auto obstacle = make_child<Obstacle>();
        obstacle->set_position({j * size - size * 0.5f * (i - 1), i * 40.0f});
      }
    }
    set_position({400 - 7.5f, 150});
  }
};

#endif // ISAAC_DEMO_OBSTACLES_HPP
