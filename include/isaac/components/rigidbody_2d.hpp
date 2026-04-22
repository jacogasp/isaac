#ifndef ISAAC_COMPONENTS_RIGIDBODY_2D_HPP
#define ISAAC_COMPONENTS_RIGIDBODY_2D_HPP

#include "isaac/components/collision_body_2d.hpp"
#include "isaac/physics/collision_shape_2d.hpp"

namespace isaac {

class RigidBody2D : public CollisionBody2D
{
  enum RigidBodyType2D
  {
    dynamic,
    kinematic,
  };

 public:
  explicit RigidBody2D(CollisionShape);

  void start(GameObject&) override;
  void update(GameObject&) override;
  void set_restitution(float restitution);
};
} // namespace isaac

#endif
