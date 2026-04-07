#ifndef ISAAC_COMPONENTS_RIGIDBODY_2D_HPP
#define ISAAC_COMPONENTS_RIGIDBODY_2D_HPP

#include "isaac/components/component.hpp"
#include "isaac/components/game_object.hpp"
#include "isaac/physics/collision_shape_2d.hpp"
#include "isaac/physics/vector.hpp"

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>

namespace isaac {

class RigidBody2D : public Component
{
  enum RigidBodyType2D
  {
    dynamic,
    kinematic,
  };

  float m_mass          = 1.0f;
  float m_gravity_scale = 1.0f;
  vec2 m_velocity       = {0.0f, 0.0f};
  vec2 m_acceleration   = {0.0f, 0.0f};

  btTransform m_transform{};
  btDefaultMotionState m_motion_state{m_transform};

  CollisionShape2D m_collision_shape;
  btRigidBody m_rigid_body;

 public:
  explicit RigidBody2D(CollisionShape2D);
  [[nodiscard]] btRigidBody& operator()();

  virtual void start(GameObject&) override;
  virtual void update(GameObject&) override;
};
} // namespace isaac

#endif
