#ifndef RENDER_WINDOW_SERVER_HPP
#define RENDER_WINDOW_SERVER_HPP

#include <sfml/Graphics.hpp>

namespace isaac {
class WindowServer
{
  sf::RenderWindow m_window;

 public:
  WindowServer();
  sf::RenderWindow* get_window();
};
} // namespace isaac
#endif
