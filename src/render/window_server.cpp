#include "render/window_server.hpp"
#include "system/defaults.hpp"

namespace isaac {
WindowServer::WindowServer()
    : m_window(
          sf::VideoMode(Defaults::k_screen_width, Defaults::k_screen_height),
          Defaults::k_window_title)
{
  m_window.setFramerateLimit(Defaults::k_max_fps);
}

sf::RenderWindow* WindowServer::get_window()
{
  return &m_window;
}
} // namespace isaac
