#include "isaac/components/sprite_renderer.hpp"
#include "isaac/components/game_object.hpp"
#include "isaac/system/service_locator.hpp"

#include <cassert>

namespace isaac {

void SpriteRenderer::start(GameObject&)
{
  m_window_server = ServiceLocator<WindowServer>::get_service();
}

void SpriteRenderer::update(GameObject& game_object)
{
  auto window = m_window_server->get_window();
  assert(window && "window server is null");
  auto const position = game_object.get_position();
  m_shape->setPosition(sf::Vector2{position.x, position.y} - m_half_bounds);
  if (m_shape) {
    window->draw(*m_shape);
  }
}
} // namespace isaac
