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
  GameObject()                            = default;
  ~GameObject()                           = default;
  GameObject(GameObject const&)           = delete;
  GameObject(GameObject&&)                = default;
  GameObject operator=(GameObject const&) = delete;

  void start();
  void update(float delta);
  void enable();
  void disable();
  [[nodiscard]] bool enabled() const;
  void set_position(vec3 position);
  [[nodiscard]] vec3 get_position() const;
  void add_child(GameObject child);
};
} // namespace isaac
#endif