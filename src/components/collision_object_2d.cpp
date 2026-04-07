#include "isaac/components/collision_object_2d.hpp"
#include "isaac/physics/physics_2d.hpp"
#include "isaac/system/service_locator.hpp"

#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionShapes/btConvexShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

namespace isaac {

CollisionObject2D::CollisionObject2D(CollisionShape2D collision_shape)
    : m_collision_shape{std::move(collision_shape)}
    , m_collision_object{}
{
  auto* shape = std::visit(CollisionShape2DVisitor{}, m_collision_shape);
  m_collision_object.setCollisionShape(shape);
  m_collision_object.setCollisionFlags(m_collision_object.getCollisionFlags()
                                       | btCollisionObject::CF_STATIC_OBJECT);
  ServiceLocator<PhysicsServer2D>::get_service()->add_collision_object(*this);
}

btCollisionObject& CollisionObject2D::operator()()
{
  return m_collision_object;
}

void CollisionObject2D::update(GameObject& go)
{
  auto pos = go.get_position();
  m_collision_object.getWorldTransform().setOrigin({pos.x, pos.y, 0});
}

} // namespace isaac
