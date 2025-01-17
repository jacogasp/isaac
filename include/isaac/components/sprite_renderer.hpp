#ifndef COMPONENTS_SPRITE_RENDERER_HPP
#define COMPONENTS_SPRITE_RENDERER_HPP

#include "component.hpp"
#include "render/window_server.hpp"
#include "system/service_locator.hpp"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace isaac {
using Shape_ptr = std::unique_ptr<sf::Shape>;
class SpriteRenderer : public Component
{
  Shape_ptr m_shape;
  sf::Vector2f m_half_bounds;
  WindowServer* m_window_server;

 public:
  void start(GameObject&) override;
  void update(GameObject&) override;
  template<typename Shape>
  Shape* make_shape();
};

template<typename Shape>
Shape* SpriteRenderer::make_shape()
{
  m_shape         = std::make_unique<Shape>();
  auto bounds     = m_shape->getLocalBounds();
  m_half_bounds.x = 0.5f * bounds.width;
  m_half_bounds.y = 0.5f * bounds.height;
  return static_cast<Shape*>(m_shape.get());
}
} // namespace isaac
#endif
