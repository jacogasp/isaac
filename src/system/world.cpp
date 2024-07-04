#include "system/world.hpp"
#include "system/defaults.hpp"
#include "system/input.hpp"
#include "system/service_locator.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace isaac {
void World::init()
{
  auto window_server = ServiceLocator<WindowServer>::get_service();
  m_window           = window_server->get_window();
  m_scene_manager    = ServiceLocator<SceneManager>::get_service();

  auto input = ServiceLocator<Input>::get_service();
  add_observer(*input);

  if (m_scene_manager->get_current_scene() == nullptr) {
    throw std::runtime_error("no scene found");
  }
  auto scene         = m_scene_manager->get_current_scene();
  auto& game_objects = scene->get_game_objects();
  std::for_each(game_objects.begin(), game_objects.end(),
                [](auto& go) { go->start(); });
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

void World::input()
{
  sf::Event event{};
  while (m_window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window->close();
      return;
    }
    notify(event);
  }
}

void World::update()
{
  auto current_scene = m_scene_manager->get_current_scene();
  assert(current_scene && "current scene is null");

  auto& game_objects = current_scene->get_game_objects();
  std::for_each(game_objects.begin(), game_objects.end(),
                [](auto& game_object) { game_object->update(0.01); });
}

void World::render()
{
  m_window->display();
}
} // namespace isaac
