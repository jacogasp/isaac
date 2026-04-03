#ifndef RENDER_WINDOW_SERVER_HPP
#define RENDER_WINDOW_SERVER_HPP

#include <SFML/System/Vector2.hpp>
#include <sfml/Graphics.hpp>
#include <string>

namespace isaac {
class WindowServer
{
  sf::RenderWindow m_window;

 public:
  WindowServer(sf::Vector2u const& window_size, std::string const& title);
  ~WindowServer();
  sf::RenderWindow* get_window();
};
} // namespace isaac
#endif
