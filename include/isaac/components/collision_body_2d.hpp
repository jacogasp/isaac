#ifndef ISAAC_PHYSICS_COLLISION_BODY_2D_HPP
#define ISAAC_PHYSICS_COLLISION_BODY_2D_HPP

#include "isaac/components/component.hpp"
#include "isaac/physics/collision_shape_2d.hpp"

#include <SFML/System/Vector2.hpp>
#include <box2d/math_functions.h>
#include <box2d/types.h>

namespace isaac {

class CollisionBody2D : public Component
{
 protected:
  CollisionShape m_collision_shape;
  b2BodyDef m_body_def;
  b2BodyId m_body_id;
  sf::Vector2f m_offset;

 public:
  explicit CollisionBody2D(CollisionShape collision_shape);

  b2BodyDef const& body_def() const;
  sf::Vector2f const& shape_offset() const;
};

} // namespace isaac

#endif
