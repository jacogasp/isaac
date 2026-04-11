#ifndef ISAAC_PHYSICS_PHYSICS_2D
#define ISAAC_PHYSICS_PHYSICS_2D

#include "isaac/components/collision_body_2d.hpp"
#include "isaac/system/logger.hpp"

#include <box2d/box2d.h>
#include <box2d/types.h>

namespace isaac {

class CollisionObject2D;
class RigidBody2D;

class DebugDrawer
{
  b2DebugDraw drawer;
  DebugDrawer();
};

template<typename T>
concept is_collision_body = std::is_base_of_v<CollisionBody2D, T>;

class PhysicsServer2D
{
  Logger& m_logger;
  b2WorldId m_world_id;
  b2DebugDraw m_debug_drawer;

 public:
  static constexpr float k_gravity = 9.81f * 100;

  PhysicsServer2D();
  ~PhysicsServer2D();

  template<is_collision_body T>
  b2BodyId create_body(T const& object)
  {
    return b2CreateBody(m_world_id, &object.body_def());
  }
  void update(float delta);
};
} // namespace isaac

#endif
