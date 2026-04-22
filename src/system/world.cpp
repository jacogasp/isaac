#include "isaac/system/world.hpp"
#include "isaac/physics/physics_2d.hpp"
#include "isaac/render/window_server.hpp"
#include "isaac/scene/scene_manager.hpp"
#include "isaac/system/input.hpp"
#include "isaac/system/service_locator.hpp"

#include <SFML/Window/Event.hpp>

#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace isaac {

World::World(WindowServer& window_server, SceneManager& scene_manager,
             PhysicsServer2D& physics_server)
    : m_window{window_server.get_window()}
    , m_scene_manager{scene_manager}
    , m_physics_server_2d{physics_server}
    , m_logger{*ServiceLocator<Logger>::get_service()}

{
  m_logger.debug("World initialized");
}

World::~World()
{
  clear();
  m_logger.debug("World destroyed");
}

void World::start()
{
  auto input = ServiceLocator<Input>::get_service();
  add_observer(*input);

  if (m_scene_manager.get_current_scene() == nullptr) {
    throw std::runtime_error("no scene found");
  }
  auto scene         = m_scene_manager.get_current_scene();
  auto& game_objects = scene->root().get_children();
}

void World::game_loop()
{
  m_logger.debug("Start game loop");
  while (m_window.isOpen()) {
    m_frame_time = m_frame_clock.restart();
    m_window.clear();
    input();
    update();
    render();
    destroy_queued();
  }
  m_logger.debug("Game loop stopped");
}

void World::input()
{
  while (auto const event = m_window.pollEvent()) {
    ImGui::SFML::ProcessEvent(m_window, *event);
    if (event->is<sf::Event::Closed>()) {
      m_logger.debug("Closing window");
      m_window.close();
    }
    notify(event.value());
  }
}

void World::update()
{
  m_physics_server_2d.update(m_frame_time.asSeconds());
  auto current_scene = m_scene_manager.get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root         = current_scene->root();
  auto& game_objects = root.get_children();
  std::ranges::for_each(game_objects, [&](auto& game_object) {
    game_object->update(m_frame_time.asSeconds());
  });
}

void World::render()
{
  auto current_scene = m_scene_manager.get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root         = current_scene->root();
  auto& game_objects = root.get_children();

  ImGui::SFML::Update(m_window, m_frame_time);
  std::ranges::for_each(
      game_objects, [&](auto& game_object) { game_object->draw(m_window); });

  // this silence the error 'Failed to set render target inactive' caused by
  // window.close()
  if (m_window.isOpen()) {
    ImGui::SFML::Render(m_window);
  }
  m_window.display();
}

void World::destroy_queued()
{
  auto current_scene = m_scene_manager.get_current_scene();
  assert(current_scene && "current scene is null");
  auto& root = current_scene->root();
  root.destroy_queued();
}

void World::clear()
{
  m_logger.debug("Clearing World");
  auto current_scene = m_scene_manager.get_current_scene();
  current_scene->root().m_children.clear();
}
} // namespace isaac
