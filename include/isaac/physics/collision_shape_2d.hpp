#ifndef ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP
#define ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP

#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

#include <variant>

namespace isaac {

using Box2DShape       = btBox2dShape;
using SphereShape      = btSphereShape;
using CollisionShape2D = std::variant<Box2DShape, SphereShape>;

struct CollisionShape2DVisitor
{
  btCollisionShape* operator()(auto& shape) const
  {
    return &shape;
  }
};

} // namespace isaac

#endif // ISAAC_PHYSICS_COLLISION_SHAPE_2D_HPP
