#include "isaac/components/collision_object_2d.hpp"
#include "isaac/physics/collision_shape_2d.hpp"
#include "isaac/physics/physics_2d.hpp"
#include "isaac/system/service_locator.hpp"
#include "isaac/system/templates.hpp"

#include <box2d/box2d.h>

namespace isaac {

CollisionObject2D::CollisionObject2D(CollisionShape collision_shape)
    : CollisionBody2D{std::move(collision_shape)}
{
  m_body_id =
      ServiceLocator<PhysicsServer2D>::get_service()->create_body(*this);
  std::visit([&](auto& shape) { shape.make_shape(m_body_id); },
             m_collision_shape);
}

void CollisionObject2D::update(GameObject& go)
{
  auto const visitor = overloads{
      [&](Box2DShape& shape) {
        auto transform = b2Body_GetTransform(m_body_id);
        auto half_size = shape.size() * 0.5f;
        b2Vec2 pos{go.get_global_position().x, go.get_global_position().y};
        auto rotation = b2Body_GetRotation(m_body_id);
        b2Body_SetTransform(m_body_id, pos + half_size, rotation);
      },
      [&](Circle2DShape& shape) {
        auto transform = b2Body_GetTransform(m_body_id);
        auto r         = shape.get_radius();
        b2Vec2 pos{go.get_global_position().x + r,
                   go.get_global_position().y + r};
        auto rotation = b2Body_GetRotation(m_body_id);
        b2Body_SetTransform(m_body_id, pos, rotation);
      }};
  std::visit(visitor, m_collision_shape);
}

} // namespace isaac
