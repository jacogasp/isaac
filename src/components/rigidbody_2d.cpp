#include "isaac/components/rigidbody_2d.hpp"
#include "isaac/components/game_object.hpp"
#include "isaac/physics/collision_shape_2d.hpp"
#include "isaac/physics/physics_2d.hpp"
#include "isaac/system/service_locator.hpp"

#include <box2d/box2d.h>

namespace isaac {

RigidBody2D::RigidBody2D(CollisionShape collision_shape)
    : CollisionBody2D{std::move(collision_shape)}
{
  m_body_def.type = b2_dynamicBody;
  m_body_id =
      ServiceLocator<PhysicsServer2D>::get_service()->create_body(*this);
  std::visit(
      [&](auto& shape) {
        auto shape_id = shape.make_shape(m_body_id);
        b2Shape_SetRestitution(shape_id, 0.9f);
      },
      m_collision_shape);
}

void RigidBody2D::start(GameObject& go)
{
  auto transform = b2Body_GetTransform(m_body_id);
  b2Vec2 pos{go.get_global_position().x, go.get_global_position().y};
  auto rotation = b2Body_GetRotation(m_body_id);
  b2Vec2 offset{m_offset.x, m_offset.y};
  b2Body_SetTransform(m_body_id, pos + offset, rotation);
}

void RigidBody2D::update(GameObject& go)
{
  auto transform = b2Body_GetTransform(m_body_id);
  sf::Vector2 pos{transform.p.x, transform.p.y};
  go.set_global_position(pos - m_offset);
}
} // namespace isaac
