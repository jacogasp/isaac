#include "isaac/physics/physics_2d.hpp"
#include "isaac/render/window_server.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/service_locator.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <box2d/box2d.h>
#include <box2d/id.h>
#include <box2d/types.h>

namespace isaac {

namespace {

void DrawPointFcn(b2Vec2 p, float size, b2HexColor color, void* context)
{
  auto& window = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::CircleShape point{size, 4};
  point.setPosition({p.x, p.y});
  window.draw(sf::CircleShape{1.f});
}

void DrawPolygonFcn(b2Vec2 const* vertices, int vertex_count, b2HexColor color,
                    void* context)
{
  auto& window = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::ConvexShape shape{static_cast<size_t>(vertex_count)};
  for (size_t i = 0; i < vertex_count; ++i) {
    shape.setPoint(i, {vertices[i].x, vertices[i].y});
  }
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color{147, 115, 165});
  shape.setOutlineThickness(1.0f);
  window.draw(shape);
}

void DrawSolidPolygonFcn(b2Transform transform, b2Vec2 const* vertices,
                         int vertex_count, float, b2HexColor, void*)
{
  auto& window = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::ConvexShape shape{static_cast<size_t>(vertex_count)};
  for (size_t i = 0; i < vertex_count; ++i) {
    shape.setPoint(i, {vertices[i].x, vertices[i].y});
  }
  shape.setPosition({transform.p.x, transform.p.y});
  shape.setFillColor(sf::Color{147, 115, 165, 75});
  window.draw(shape);
}

void DrawCircleFcn(b2Vec2 center, float radius, b2HexColor color, void* context)
{
  auto& window = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::CircleShape circle{radius};
  circle.setPosition({center.x, center.y});
  window.draw(circle);
}

void DrawSolidCircleFcn(b2Transform transform, float radius, b2HexColor color,
                        void* context)
{
  auto& window = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::CircleShape circle{radius};
  circle.setPosition({transform.p.x - radius, transform.p.y - radius});
  window.draw(circle);
}

void DrawSegmentFcn(b2Vec2 a, b2Vec2 b, b2HexColor color, void* context)
{
  auto& window      = ServiceLocator<WindowServer>::get_service()->get_window();
  sf::Vertex line[] = {sf::Vertex{{a.x, a.y}}, sf::Vertex{{b.x, b.y}}};
  window.draw(line, 2, sf::PrimitiveType::Lines);
}

} // namespace

DebugDrawer::DebugDrawer()
    : drawer{b2DefaultDebugDraw()}
{}

PhysicsServer2D::PhysicsServer2D()
    : m_logger(*ServiceLocator<Logger>::get_service())
    , m_debug_drawer{b2DefaultDebugDraw()}
{
  m_debug_drawer.DrawPointFcn        = DrawPointFcn;
  m_debug_drawer.DrawPolygonFcn      = DrawPolygonFcn;
  m_debug_drawer.DrawSolidPolygonFcn = DrawSolidPolygonFcn;
  m_debug_drawer.DrawCircleFcn       = DrawCircleFcn;
  m_debug_drawer.DrawSolidCircleFcn  = DrawSolidCircleFcn;
  m_debug_drawer.DrawSegmentFcn      = DrawSegmentFcn;
  m_debug_drawer.drawShapes          = true;
  m_debug_drawer.drawBounds          = true;
  m_debug_drawer.context             = this;

  auto world_def    = b2DefaultWorldDef();
  world_def.gravity = {0, k_gravity};
  m_world_id        = b2CreateWorld(&world_def);
  m_logger.debug("PhysicsServer2D initialized");
}

PhysicsServer2D::~PhysicsServer2D()
{
  b2DestroyWorld(m_world_id);
  m_logger.debug("PhysicServer2D shutdown");
}

void PhysicsServer2D::update(float delta)
{
  b2World_Step(m_world_id, delta, 4);
  b2World_Draw(m_world_id, &m_debug_drawer);
}
} // namespace isaac
