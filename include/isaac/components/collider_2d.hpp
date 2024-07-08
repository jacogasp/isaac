#ifndef COMPONENTS_COLLIDER_2D_HPP
#define COMPONENTS_COLLIDER_2D_HPP

#include "component.hpp"
#include "physics/collision_shape_2d.hpp"

namespace isaac {
class GameObject;

class Collider2D : public Component
{
  CollisionShape2D m_collision_shape{};

 public:
  ~Collider2D() final;
  void set_collision_shape(CollisionShape2D);
  [[nodiscard]] CollisionShape2D const& collision_shape() const;
  void start(GameObject&) override;
  void update(GameObject&) override;
};
} // namespace isaac
#endif
