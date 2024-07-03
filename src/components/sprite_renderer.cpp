#include "components/sprite_renderer.hpp"

#include <cassert>
#include <utility>

namespace isaac {

void SpriteRenderer::start()
{
  m_window_server = ServiceLocator<WindowServer>::get_service();
}

void SpriteRenderer::update(GameObject&)
{
  auto window = m_window_server->get_window();
  assert(window && "window server is null");
  if (m_shape) {
    window->draw(*m_shape);
  }
}
} // namespace isaac
