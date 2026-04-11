#ifndef ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP
#define ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>

#include <variant>

namespace isaac {

class Box2DShape;
class Circle2DShape;

using CollisionShape = std::variant<Box2DShape, Circle2DShape>;

class CollisionShapeBase
{
  b2ShapeDef m_shape_def{b2DefaultShapeDef()};

 public:
  b2ShapeDef const& shape_def() const;
  virtual b2ShapeId make_shape(b2BodyId body) = 0;
};

class Box2DShape : public CollisionShapeBase
{
  b2Polygon m_polygon;
  b2Vec2 m_size;

 public:
  explicit Box2DShape(sf::Vector2f size);
  b2Vec2 const& size() const;
  b2ShapeId make_shape(b2BodyId body) override;
};

class Circle2DShape : public CollisionShapeBase
{
  b2Circle m_circle;
  float m_radius;

 public:
  explicit Circle2DShape(float radius);
  float get_radius() const;
  b2ShapeId make_shape(b2BodyId body) override;
};

} // namespace isaac

#endif // ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP
