#ifndef COMPONENTS_COMPONENT_HPP
#define COMPONENTS_COMPONENT_HPP

namespace isaac {
class GameObject;
class Component
{
 public:
  virtual ~Component() = default;
  virtual void start() {};
  virtual void update(GameObject& game_object) {};
};
} // namespace isaac

#endif