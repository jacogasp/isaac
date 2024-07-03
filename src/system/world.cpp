#include "system/world.hpp"
#include "system/defaults.hpp"
#include "system/service_locator.hpp"

#include <algorithm>

namespace isaac {
World::World()
{
  m_scene_manager    = ServiceLocator<SceneManager>::get_service();
  auto window_server = ServiceLocator<WindowServer>::get_service();
  m_window           = window_server->get_window();
}

void World::input()
{
  sf::Event event{};
  while (m_window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window->close();
      return;
    }
  }
}

void World::update()
{
  auto current_scene = m_scene_manager->get_current_scene();
  auto& game_objects = current_scene->get_game_objects();
  // std::for_each(game_objects.begin(), game_objects.end(),
  //               [](auto& game_object) {
  //                 game_object.update(0.01);
  //               });
}

void World::render()
{
  m_window->display();
}

void World::game_loop()
{
  while (m_window->isOpen()) {
    m_window->clear();
    input();
    update();
    render();
  }
}
} // namespace isaac