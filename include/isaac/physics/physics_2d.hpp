#ifndef PHYSICS_PHYSICS_2D
#define PHYSICS_PHYSICS_2D

#include "components/collider_2d.hpp"
#include "components/game_object.hpp"
#include "physics/collision_2d.hpp"
#include "physics/quad_tree.hpp"

#include <cstddef>
#include <optional>
#include <unordered_map>

namespace isaac {
class PhysicsServer2D
{
  std::unordered_map<std::size_t, Collider2D*> m_colliders{};

  QuadTree<Collider2D, 4, 16> m_quad_tree{
      Rectangle2D{{-2'500, -2'500}, {7'500, 7'500}}};

 public:
  static constexpr float k_gravity = 9.81f;
  void add_collider(Collider2D* collider);
  void remove_collider(std::size_t id);
  std::optional<Collision2D> resolve_collision(Collider2D& collider);
  void update();
};
} // namespace isaac

#endif