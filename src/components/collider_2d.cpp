#include "components/collider_2d.hpp"
#include "components/game_object.hpp"
#include "physics/physics_2d.hpp"
#include "system/service_locator.hpp"

namespace isaac {
Collider2D::~Collider2D()
{
  auto physics = ServiceLocator<PhysicsServer2D>::get_service();
  physics->remove_collider(id());
}

void Collider2D::set_collision_shape(CollisionShape2D collision_shape)
{
  m_collision_shape = collision_shape;
}

CollisionShape2D const& Collider2D::collision_shape() const
{
  return m_collision_shape;
}

void Collider2D::start(GameObject& game_object)
{
  auto physics = ServiceLocator<PhysicsServer2D>::get_service();
  physics->add_collider(this);
  auto go_position = game_object.get_position();
  m_collision_shape.set_position({go_position.x, go_position.y});
}

void Collider2D::update(GameObject& game_object)
{
  auto go_position = game_object.get_position();
  m_collision_shape.set_position({go_position.x, go_position.y});
  auto physics   = ServiceLocator<PhysicsServer2D>::get_service();
  auto collision = physics->resolve_collision(*this);
  if (collision.has_value()) {
    game_object.on_collision_2d(collision.value());
  }
}
} // namespace isaac
