#ifndef COMPONENTS_GAME_OBJECT_HPP
#define COMPONENTS_GAME_OBJECT_HPP

#include "physics/vector.hpp"
#include <vector>

namespace isaac {
class GameObject
{
  vec3 m_position{};
  bool m_disabled = false;
  std::vector<GameObject> m_children{};

 protected:
  virtual void on_start() {};
  virtual void on_update(float delta) {};

 public:
  void start();
  void update(float delta);
  void enable();
  void disable();
  [[nodiscard]] bool enabled() const;
  void set_position(vec3 position);
  [[nodiscard]] vec3 get_position() const;
};
} // namespace isaac
#endif