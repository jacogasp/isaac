#ifndef ISAAC_DEMO_WALLS_HPP
#define ISAAC_DEMO_WALLS_HPP

#include <isaac/components/collision_object_2d.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/shape_renderer.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

struct WallData
{
  sf::Vector2f position;
  sf::Vector2f size;
};

class Wall : public isaac::GameObject
{
 public:
  Wall(WallData data)
  {
    isaac::Box2DShape box{data.size};
    auto collider       = make_component<isaac::CollisionObject2D>(box);
    auto shape_renderer = make_component<isaac::ShapeRenderer>();
    auto& shape = shape_renderer->make_shape<sf::RectangleShape>(data.size);
    set_position(data.position);
  }
};

class Walls : public isaac::GameObject
{
  auto static constexpr s_wall_thickness = 10;
  std::vector<WallData> m_walls{
      {{0, 0}, {s_wall_thickness, 550}},                      // left
      {{750, 0}, {s_wall_thickness, 550}},                    // right
      {{0, 0}, {750, s_wall_thickness}},                      // top
      {{0, 550 - s_wall_thickness}, {750, s_wall_thickness}}, // bottom
  };

  void on_start() override
  {
    for (auto&& wall : m_walls) {
      make_child<Wall>(wall);
    }
    set_position({25, 25});
  }
};
#endif // ISAAC_DEMO_WALLS_HPP
