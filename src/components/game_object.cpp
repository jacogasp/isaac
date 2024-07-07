#include "components/game_object.hpp"

#include <algorithm>

namespace isaac {
void GameObject::start()
{
  on_start();
  std::for_each(m_components.begin(), m_components.end(),
                [&](auto& component) { component->start(); });
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child->start(); });
}

void GameObject::update(float delta)
{
  on_update(delta);
  std::for_each(m_components.begin(), m_components.end(),
                [this](auto& component) { component->update(*this); });
  std::for_each(m_children.begin(), m_children.end(),
                [delta](auto& child) { child->update(delta); });
}

void GameObject::enable()
{
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child->enable(); });
  m_enabled = true;
}

void GameObject::disable()
{
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child->disable(); });
  m_enabled = false;
}

bool GameObject::enabled() const
{
  return !m_enabled;
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
} // namespace isaac
