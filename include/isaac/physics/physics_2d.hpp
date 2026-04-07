#ifndef ISAAC_PHYSICS_PHYSICS_2D
#define ISAAC_PHYSICS_PHYSICS_2D

#include "isaac/system/logger.hpp"

#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>

namespace isaac {

class CollisionObject2D;
class RigidBody2D;

class PhysicsServer2D
{
  Logger& m_logger;
  btDefaultCollisionConfiguration m_collision_configuration{};
  btCollisionDispatcher m_dispatcher{&m_collision_configuration};
  btDbvtBroadphase m_overlapping_pair_cache{};
  btSequentialImpulseConstraintSolver m_solver{};
  btDiscreteDynamicsWorld m_dynamics_world{&m_dispatcher,
                                           &m_overlapping_pair_cache, &m_solver,
                                           &m_collision_configuration};

 public:
  static constexpr float k_gravity = 9.81f * 100;

  PhysicsServer2D();
  ~PhysicsServer2D();

  void add_rigid_body(RigidBody2D&);
  void add_collision_object(CollisionObject2D&);
  void update(float delta);
};
} // namespace isaac

#endif
