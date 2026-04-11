#include "isaac/components/collision_body_2d.hpp"
#include "isaac/system/templates.hpp"

#include <SFML/System/Vector2.hpp>
#include <box2d/math_functions.h>
#include <box2d/types.h>

namespace isaac {

CollisionBody2D::CollisionBody2D(CollisionShape collision_shape)
    : m_collision_shape{std::move(collision_shape)}
    , m_body_def{b2DefaultBodyDef()}
    , m_body_id{}
{
  auto const visitor = overloads{
      [&](Box2DShape const& shape) {
        m_offset = sf::Vector2f{shape.size().x, shape.size().y} * 0.5f;
      },
      [&](Circle2DShape const& shape) {
        m_offset = {shape.get_radius(), shape.get_radius()};
      },
  };
  std::visit(visitor, m_collision_shape);
}

b2BodyDef const& CollisionBody2D::body_def() const
{
  return m_body_def;
}

sf::Vector2f const& CollisionBody2D::shape_offset() const
{
  return m_offset;
}

} // namespace isaac
