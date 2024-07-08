#include "physics/physics_2d.hpp"

#include <algorithm>

namespace isaac {

void PhysicsServer2D::add_collider(Collider2D* collider)
{
  m_colliders.emplace(collider->id(), collider);
}

void PhysicsServer2D::remove_collider(std::size_t id)
{
  m_colliders.erase(id);
}

std::optional<Collision2D>
PhysicsServer2D::resolve_collision(Collider2D& collider)
{
  auto& collision_shape = collider.collision_shape();
  auto area             = collision_shape.bounds();
  auto result           = m_quad_tree.query(area);
  for (auto other : result) {
    auto other_collider = other->object;
    if (other_collider == &collider) {
      continue;
    }
    auto& other_shape = other_collider->collision_shape();
    if (collision_shape.intersects(other_shape)) {
      Collision2D collision;
      collision.collider = &collider;
      collision.other    = other->object;
      return std::optional{collision};
    }
  }
  return std::nullopt;
}

void PhysicsServer2D::update()
{
  m_quad_tree.reset();
  std::ranges::for_each(m_colliders, [&](auto& collider) {
    QuadTreeData<Collider2D> data{};
    data.bounds = collider.second->collision_shape().bounds();
    data.object = collider.second;
    m_quad_tree.insert(data);
  });
}
} // namespace isaac
