#include "isaac/physics/physics_2d.hpp"
#include "isaac/components/collision_object_2d.hpp"
#include "isaac/components/rigidbody_2d.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/service_locator.hpp"

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btIDebugDraw.h>
#include <LinearMath/btTransform.h>
#include <btBulletCollisionCommon.h>

namespace isaac {

PhysicsServer2D::PhysicsServer2D()
    : m_logger(*ServiceLocator<Logger>::get_service())
{
  m_dynamics_world.setGravity({0, k_gravity, 0});
  m_logger.debug("PhysicsServer2D initialized");
}

PhysicsServer2D::~PhysicsServer2D()
{
  for (size_t i = 0; i < m_dynamics_world.getNumCollisionObjects(); ++i) {
    auto obj = m_dynamics_world.getCollisionObjectArray()[i];
    m_dynamics_world.removeCollisionObject(obj);
  }
  m_logger.debug("PhysicServer2D shutdown");
}

void PhysicsServer2D::add_rigid_body(RigidBody2D& body)
{
  m_dynamics_world.addRigidBody(&body());
}

void PhysicsServer2D::add_collision_object(CollisionObject2D& object)
{
  m_dynamics_world.addCollisionObject(&object());
}

void PhysicsServer2D::update(float delta)
{
  m_dynamics_world.stepSimulation(delta, 10);
  for (size_t i = 0; i < m_dynamics_world.getNumCollisionObjects(); ++i) {
    auto obj = m_dynamics_world.getCollisionObjectArray()[i];
    continue;
    auto body = btRigidBody::upcast(obj);
    btTransform transform;
    if (body && body->getMotionState()) {
      assert(body->getMotionState());
      body->getMotionState()->getWorldTransform(transform);
    } else {
      transform = obj->getWorldTransform();
    }
  }
}
} // namespace isaac
