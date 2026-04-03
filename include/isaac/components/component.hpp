#ifndef ISAAC_COMPONENTS_COMPONENT_HPP
#define ISAAC_COMPONENTS_COMPONENT_HPP

#include "isaac/internal/base_object.hpp"
namespace isaac {
class GameObject;
class Component : public BaseObject
{
  GameObject* m_parent;
  friend class GameObject;

 public:
  virtual ~Component() = default;
  [[nodiscard]] GameObject* game_object();
  virtual void start(GameObject& game_object) {};
  virtual void update(GameObject& game_object) {};
};
} // namespace isaac
#endif
