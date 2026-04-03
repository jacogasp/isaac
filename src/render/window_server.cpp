#include "isaac/render/window_server.hpp"
#include "isaac/system/defaults.hpp"
#include <SFML/System/Vector2.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include <cstdlib>

namespace isaac {
WindowServer::WindowServer(sf::Vector2u const& window_size,
                           std::string const& title)
    : m_window(sf::VideoMode(window_size), title)
{
  m_window.setFramerateLimit(Defaults::k_max_fps);
  if (!ImGui::SFML::Init(m_window)) {
    std::exit(EXIT_FAILURE);
  }
  auto& io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
}

WindowServer::~WindowServer()
{
  ImGui::SFML::Shutdown();
}

sf::RenderWindow* WindowServer::get_window()
{
  return &m_window;
}
} // namespace isaac
