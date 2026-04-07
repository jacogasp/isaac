#include "isaac/components/rigidbody_2d.hpp"

#include "isaac/physics/physics_2d.hpp"
#include "isaac/physics/vector.hpp"
#include "isaac/system/service_locator.hpp"

#include <BulletCollision/CollisionShapes/btBox2dShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

namespace isaac {

btRigidBody make_rigid_body(CollisionShape2D& collision_shape,
                            btMotionState& motion_state, float mass)
{
  auto shape = std::visit(CollisionShape2DVisitor{}, collision_shape);
  btVector3 local_inertia{0.0f, 0.0f, 0.0f};

  shape->calculateLocalInertia(mass, local_inertia);
  btRigidBody::btRigidBodyConstructionInfo rb_info{mass, &motion_state, shape,
                                                   local_inertia};
  return btRigidBody{rb_info};
}

RigidBody2D::RigidBody2D(CollisionShape2D collision_shape)
    : m_collision_shape{std::move(collision_shape)}
    , m_rigid_body{make_rigid_body(m_collision_shape, m_motion_state, m_mass)}
{
  m_rigid_body.setRestitution(1.0);
  m_rigid_body.setFriction(0.9f);
  m_rigid_body.setDamping(0.2f, 0.f);
  ServiceLocator<PhysicsServer2D>::get_service()->add_rigid_body(*this);
}

btRigidBody& RigidBody2D::operator()()
{
  return m_rigid_body;
}

void RigidBody2D::start(GameObject& go)
{
  auto pos = go.get_position();
  m_rigid_body.getWorldTransform().setOrigin({pos.x, pos.y, 0});
}

void RigidBody2D::update(GameObject& go)
{
  btTransform t;
  m_rigid_body.getMotionState()->getWorldTransform(t);
  auto const& pos = t.getOrigin();
  go.set_position(vec3{pos.x(), pos.y(), 0.0f});
}
} // namespace isaac
