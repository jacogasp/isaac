#include "isaac/system/world.hpp"
#include "isaac/system/input.hpp"
#include "isaac/system/service_locator.hpp"

#include <SFML/Window/Event.hpp>

#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace isaac {
void World::start()
{
  auto window_server  = ServiceLocator<WindowServer>::get_service();
  m_scene_manager     = ServiceLocator<SceneManager>::get_service();
  m_physics_server_2d = ServiceLocator<PhysicsServer2D>::get_service();
  auto input          = ServiceLocator<Input>::get_service();
  add_observer(*input);

  if (m_scene_manager->get_current_scene() == nullptr) {
    throw std::runtime_error("no scene found");
  }

  m_window           = window_server->get_window();
  auto scene         = m_scene_manager->get_current_scene();
  auto& game_objects = scene->root().get_children();
  // start all game objects and their children/components
  std::ranges::for_each(game_objects, [](auto& go) { go->start(); });
}

void World::game_loop()
{
  while (m_window->isOpen()) {
    m_window->clear();
    input();
    update();
    render();
    destroy_queued();
  }
}

void World::input()
{
  while (auto const event = m_window->pollEvent()) {
    ImGui::SFML::ProcessEvent(*m_window, *event);
    if (event->is<sf::Event::Closed>()) {
      m_window->close();
      return;
    }
    notify(event.value());
  }
}

void World::update()
{
  auto const delta = m_frame_clock.restart();
  ImGui::SFML::Update(*m_window, delta);
  m_physics_server_2d->update();
  auto current_scene = m_scene_manager->get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root         = current_scene->root();
  auto& game_objects = root.get_children();
  std::ranges::for_each(game_objects, [&delta](auto& game_object) {
    game_object->update(delta.asSeconds());
  });
}

void World::render()
{
  auto current_scene = m_scene_manager->get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root         = current_scene->root();
  auto& game_objects = root.get_children();
  std::ranges::for_each(game_objects,
                        [](auto& game_object) { game_object->draw(); });
  ImGui::SFML::Render(*m_window);
  m_window->display();
}

void World::destroy_queued()
{
  auto current_scene = m_scene_manager->get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root = current_scene->root();
  root.destroy_queued();
}

void World::clear()
{
  auto current_scene = m_scene_manager->get_current_scene();
  current_scene->root().m_children.clear();
}
} // namespace isaac
