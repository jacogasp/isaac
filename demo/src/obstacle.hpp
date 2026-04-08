#ifndef ISAAC_DEMO_OBSTACLE_HPP
#define ISAAC_DEMO_OBSTACLE_HPP

#include <isaac/components/collision_object_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/shape_renderer.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

struct Wall
{
  sf::Vector2f position;
  sf::Vector2f size;
};

class Obstacle : public isaac::GameObject
{
  auto static constexpr s_wall_thickness = 10;
  auto static constexpr s_wall_length    = 400;

  std::vector<Wall> m_walls{
      {{0, 0}, {s_wall_thickness, s_wall_length}},             // left
      {{s_wall_length, 0}, {s_wall_thickness, s_wall_length}}, // right
      {{0, 0}, {s_wall_length, s_wall_thickness}},             // top
      {{0, s_wall_length - s_wall_thickness},
       {s_wall_length, s_wall_thickness}}, // bottom
  };

  void on_start() override
  {
    for (auto&& wall : m_walls) {
      auto shape_renderer = make_component<isaac::ShapeRenderer>();
      auto& shape = shape_renderer->make_shape<sf::RectangleShape>(wall.size);
      shape.setPosition(wall.position);
    }
    set_position({100, 100});
  }

  void on_destroy() override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("Obstacle destroyed!");
  }
};
#endif // ISAAC_DEMO_OBSTACLE_HPP
