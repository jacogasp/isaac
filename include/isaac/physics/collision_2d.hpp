#ifndef PHYSICS_COLLISION_2D_HPP
#define PHYSICS_COLLISION_2D_HPP

namespace isaac {
class Collider2D;
class GameObject;
struct Collision2D
{
  Collider2D* collider;
  Collider2D* other;
};
} // namespace isaac
#endif
