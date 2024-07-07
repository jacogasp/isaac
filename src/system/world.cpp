#include "system/world.hpp"
#include "system/defaults.hpp"
#include "system/input.hpp"
#include "system/service_locator.hpp"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace isaac {
void World::start()
{
  auto window_server = ServiceLocator<WindowServer>::get_service();
  m_scene_manager    = ServiceLocator<SceneManager>::get_service();
  auto input         = ServiceLocator<Input>::get_service();
  add_observer(*input);

  if (m_scene_manager->get_current_scene() == nullptr) {
    throw std::runtime_error("no scene found");
  }

  m_window           = window_server->get_window();
  auto scene         = m_scene_manager->get_current_scene();
  auto& game_objects = scene->get_game_objects();
  // start all game objects and their children/components
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
  auto const delta   = m_frame_clock.restart().asSeconds();
  auto current_scene = m_scene_manager->get_current_scene();
  assert(current_scene && "current scene is null");

  auto& game_objects = current_scene->get_game_objects();
  std::for_each(game_objects.begin(), game_objects.end(),
                [&delta](auto& game_object) { game_object->update(delta); });
}

void World::render()
{
  m_window->display();
}
} // namespace isaac
