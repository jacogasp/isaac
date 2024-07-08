#include "components/game_object.hpp"

#include <algorithm>
#include <cassert>
#include <ranges>

namespace isaac {

void GameObject::start()
{
  on_start();
  std::ranges::for_each(m_components, [&](auto& comp) { comp->start(*this); });
  std::ranges::for_each(m_children, [](auto& child) { child->start(); });
}

void GameObject::update(float delta)
{
  on_update(delta);
  std::ranges::for_each(m_components,
                        [this](auto& comp) { comp->update(*this); });
  std::ranges::for_each(m_children,
                        [delta](auto& child) { child->update(delta); });
}

void GameObject::destroy_queued()
{
  // recursively destroy_queued children
  std::ranges::for_each(m_children,
                        [](auto& child) { child->destroy_queued(); });

  auto to_erase = std::ranges::partition(m_children, [&](auto& child) {
    return !m_child_ids_to_erase.contains(child->id());
  });

  std::ranges::for_each(to_erase, [](auto& child) { child->on_destroy(); });
  m_children.erase(to_erase.begin(), to_erase.end());
  m_child_ids_to_erase.clear();
}

void GameObject::enable()
{
  std::ranges::for_each(m_children, [](auto& child) { child->enable(); });
  m_enabled = true;
}

void GameObject::disable()
{
  std::ranges::for_each(m_children, [](auto& child) { child->disable(); });
  m_enabled = false;
}

bool GameObject::enabled() const
{
  return !m_enabled;
}

void GameObject::destroy()
{
  assert(m_parent && "parent is null");
  m_parent->m_child_ids_to_erase.emplace(id());
}

void GameObject::set_position(vec3 const& position)
{
  std::ranges::for_each(m_children, [&](auto& child) {
    auto const offset = get_position() - child->get_position();
    child->set_position(position + offset);
  });
  m_position = position;
}

vec3 GameObject::get_position() const
{
  return m_position;
}

std::vector<GameObject_ptr>& GameObject::get_children()
{
  return m_children;
}

std::vector<GameObject_ptr> const& GameObject::get_children() const
{
  return m_children;
}
} // namespace isaac
