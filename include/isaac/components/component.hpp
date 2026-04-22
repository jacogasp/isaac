#ifndef ISAAC_COMPONENTS_COMPONENT_HPP
#define ISAAC_COMPONENTS_COMPONENT_HPP

#include "isaac/internal/base_object.hpp"

namespace sf {
class RenderWindow;
}

namespace isaac {

class GameObject;

class Component : public BaseObject
{
  GameObject* m_parent;
  friend class GameObject;

 public:
  Component()                           = default;
  Component(Component const&)           = delete;
  Component(Component&&)                = default;
  Component operator=(Component const&) = delete;
  virtual ~Component()                  = default;

  [[nodiscard]] GameObject* game_object();
  virtual void start(GameObject& game_object) {};
  virtual void update(GameObject& game_object) {};
  virtual void draw(GameObject& game_object, sf::RenderWindow& window) {};
};
} // namespace isaac
#endif
