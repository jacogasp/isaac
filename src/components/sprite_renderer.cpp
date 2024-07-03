#include "components/sprite_renderer.hpp"

#include <algorithm>
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
  std::for_each(m_shapes.begin(), m_shapes.end(),
                [window](auto& shape) { window->draw(*shape); });
}
} // namespace isaac
