#ifndef COMPONENTS_COMPONENT_HPP
#define COMPONENTS_COMPONENT_HPP

namespace isaac {
class GameObject;
class Component
{
 public:
  virtual ~Component()                         = default;
  virtual void update(GameObject& game_object) = 0;
};
} // namespace isaac

#endif