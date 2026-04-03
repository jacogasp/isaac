#ifndef RENDER_WINDOW_SERVER_HPP
#define RENDER_WINDOW_SERVER_HPP

#include <sfml/Graphics.hpp>
#include <string>

namespace isaac {
class WindowServer
{
  sf::RenderWindow m_window;

 public:
  WindowServer(std::string const& title);
  sf::RenderWindow* get_window();
};
} // namespace isaac
#endif
