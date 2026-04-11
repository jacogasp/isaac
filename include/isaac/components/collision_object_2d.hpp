#ifndef ISAAC_COMPONENTS_COLLISION_OBJECT_2D_HPP
#define ISAAC_COMPONENTS_COLLISION_OBJECT_2D_HPP

#include "isaac/components/collision_body_2d.hpp"
#include "isaac/components/component.hpp"
#include "isaac/components/game_object.hpp"
#include "isaac/physics/collision_shape_2d.hpp"

#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>

namespace isaac {

class CollisionObject2D : public CollisionBody2D
{
 public:
  explicit CollisionObject2D(CollisionShape);

  virtual void update(GameObject&) override;
};

} // namespace isaac

#endif
