#ifndef COMPONENTS_GAME_OBJECT_HPP
#define COMPONENTS_GAME_OBJECT_HPP

#include "components/component.hpp"
#include "physics/vector.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace isaac {
class GameObject
{
  vec3 m_position{};
  bool m_enabled = false;
  std::vector<GameObject> m_children{};
  std::vector<std::unique_ptr<Component>> m_components{};

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
  template<typename T>
  T* make_component();
  template<typename T>
  T* get_component() const;
};

template<typename T>
T* GameObject::make_component()
{
  m_components.push_back(std::make_unique<T>());
  return static_cast<T*>(m_components.back().get());
};

template<typename T>
T* GameObject::get_component() const
{
  for (auto& component : m_components) {
    auto found = dynamic_cast<T*>(component.get());
    if (found) {
      return found;
    }
  }
  return nullptr;
}
} // namespace isaac
#endif
