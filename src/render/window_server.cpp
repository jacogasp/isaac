#include "isaac/render/window_server.hpp"
#include "isaac/system/defaults.hpp"

#include <cstdlib>

namespace isaac {
WindowServer::WindowServer(std::string const& title)
    : m_window(
          sf::VideoMode({Defaults::k_screen_width, Defaults::k_screen_height}),
          title)
{
  m_window.setFramerateLimit(Defaults::k_max_fps);
}

sf::RenderWindow* WindowServer::get_window()
{
  return &m_window;
}
} // namespace isaac
