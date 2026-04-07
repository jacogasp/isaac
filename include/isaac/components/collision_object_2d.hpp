#ifndef ISAAC_COMPONENTS_COLLISION_OBJECT_2D_HPP
#define ISAAC_COMPONENTS_COLLISION_OBJECT_2D_HPP

#include "isaac/components/component.hpp"
#include "isaac/components/game_object.hpp"
#include "isaac/physics/collision_shape_2d.hpp"

#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btTransform.h>

namespace isaac {

class CollisionObject2D : public Component
{
 protected:
  CollisionShape2D m_collision_shape;
  btCollisionObject m_collision_object;

 public:
  explicit CollisionObject2D(CollisionShape2D);
  [[nodiscard]] btCollisionObject& operator()();

  virtual void update(GameObject&) override;
};

} // namespace isaac

#endif
