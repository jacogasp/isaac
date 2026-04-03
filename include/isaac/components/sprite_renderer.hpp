#ifndef ISAAC_COMPONENTS_SPRITE_RENDERER_HPP
#define ISAAC_COMPONENTS_SPRITE_RENDERER_HPP

#include "isaac/components/component.hpp"
#include "isaac/render/window_server.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

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
  m_half_bounds.x = 0.5f * bounds.size.x;
  m_half_bounds.y = 0.5f * bounds.size.y;
  return static_cast<Shape*>(m_shape.get());
}
} // namespace isaac
#endif
