#ifndef COMPONENTS_GAME_OBJECT_HPP
#define COMPONENTS_GAME_OBJECT_HPP

#include "components/component.hpp"
#include "internal/base_object.hpp"
#include "physics/vector.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace isaac {
using GameObject_ptr = std::unique_ptr<GameObject>;
using Component_ptr  = std::unique_ptr<Component>;
class GameObject : public BaseObject
{
  vec3 m_position{};
  bool m_enabled = false;
  std::vector<GameObject_ptr> m_children{};
  std::vector<Component_ptr> m_components{};
  std::vector<std::size_t> m_child_ids_to_erase{};
  GameObject* m_parent = nullptr;

 private:
  void start();
  void update(float delta);
  void destroy_queued();
  [[nodiscard]] std::vector<GameObject_ptr>& get_children();
  friend class World;

 protected:
  virtual void on_start() {};
  virtual void on_update(float delta) {};
  virtual void on_destroy() {};

 public:
  GameObject()                            = default;
  ~GameObject()                           = default;
  GameObject(GameObject const&)           = delete;
  GameObject(GameObject&&)                = default;
  GameObject operator=(GameObject const&) = delete;

  void enable();
  void disable();
  [[nodiscard]] bool enabled() const;
  void destroy();
  void set_position(vec3 position);
  [[nodiscard]] vec3 get_position() const;
  template<typename T, typename... Args>
  T* make_child(Args... args);
  [[nodiscard]] std::vector<GameObject_ptr> const& get_children() const;
  template<typename T>
  T* make_component();
  template<typename T>
  T* get_component() const;
};

template<typename T, typename... Args>
T* GameObject::make_child(Args... args)
{
  m_children.push_back(std::make_unique<T>(args...));
  m_children.back()->m_parent = this;
  return static_cast<T*>(m_children.back().get());
}

template<typename T>
T* GameObject::make_component()
{
  m_components.push_back(std::make_unique<T>());
  m_components.back()->m_parent = this;
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
