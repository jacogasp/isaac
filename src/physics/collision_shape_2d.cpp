#include "isaac/physics/collision_shape_2d.hpp"
#include <box2d/box2d.h>
#include <box2d/id.h>
#include <box2d/types.h>

namespace isaac {

b2ShapeDef const& CollisionShapeBase::shape_def() const
{
  return m_shape_def;
}

Box2DShape::Box2DShape(sf::Vector2f size)
    : m_polygon{b2MakeBox(size.x / 2.f, size.y / 2.f)}
    , m_size{size.x, size.y}
{}

b2Vec2 const& Box2DShape::size() const
{
  return m_size;
}

b2ShapeId Box2DShape::make_shape(b2BodyId body_id)
{
  return b2CreatePolygonShape(body_id, &shape_def(), &m_polygon);
}

Circle2DShape::Circle2DShape(float radius)
    : m_circle{0, 0, radius}
    , m_radius{radius}
{}

float Circle2DShape::get_radius() const
{
  return m_radius;
}

b2ShapeId Circle2DShape::make_shape(b2BodyId body_id)
{
  return b2CreateCircleShape(body_id, &shape_def(), &m_circle);
}

} // namespace isaac
