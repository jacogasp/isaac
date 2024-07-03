#include "components/game_object.hpp"

#include <algorithm>

namespace isaac {
void GameObject::start()
{
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child.start(); });
  on_start();
}

void GameObject::update(float delta)
{
  std::for_each(m_children.begin(), m_children.end(),
                [delta](auto& child) { child.update(delta); });
  on_update(delta);
}

void GameObject::enable()
{
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child.enable(); });
  m_disabled = false;
}

void GameObject::disable()
{
  std::for_each(m_children.begin(), m_children.end(),
                [](auto& child) { child.disable(); });
  m_disabled = true;
}

bool GameObject::enabled() const
{
  return !m_disabled;
}

void GameObject::set_position(vec3 position)
{
  std::for_each(m_children.begin(), m_children.end(),
                [&, position](auto& child) {
                  auto const offset = get_position() - child.get_position();
                  child.set_position(position + offset);
                });
  m_position = position;
}

vec3 GameObject::get_position() const
{
  return m_position;
}
void GameObject::add_child(GameObject child)
{
  m_children.push_back(std::move(child));
}

} // namespace isaac
