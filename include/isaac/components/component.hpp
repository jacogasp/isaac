#ifndef COMPONENTS_COMPONENT_HPP
#define COMPONENTS_COMPONENT_HPP

#include "internal/base_object.hpp"
namespace isaac {
class GameObject;
class Component : public BaseObject
{
  GameObject* m_parent;
  friend class GameObject;

 public:
  virtual ~Component() = default;
  [[nodiscard]] GameObject* game_object();
  virtual void update(GameObject& game_object) {};
};
} // namespace isaac
#endif
