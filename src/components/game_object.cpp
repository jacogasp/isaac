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
  if (m_child_ids_to_erase.empty()) {
    return;
  }

  auto to_erase =
      std::partition(m_children.begin(), m_children.end(), [&](auto& child) {
        auto found = std::find_if(
            m_child_ids_to_erase.begin(), m_child_ids_to_erase.end(),
            [&child](auto id) { return child->id() == id; });
        return found == m_child_ids_to_erase.end();
      });
  std::for_each(to_erase, m_children.end(),
                [](auto& child) { child->on_destroy(); });
  m_children.erase(to_erase, m_children.end());
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
  m_parent->m_child_ids_to_erase.push_back(id());
}

void GameObject::set_position(vec3 position)
{
  std::for_each(m_children.begin(), m_children.end(),
                [&, position](auto& child) {
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
