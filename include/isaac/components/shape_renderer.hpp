#ifndef ISAAC_COMPONENTS_SPRITE_RENDERER_HPP
#define ISAAC_COMPONENTS_SPRITE_RENDERER_HPP

#include "isaac/components/component.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

namespace sf {
class RenderWindow;
}

namespace isaac {

using Shape_ptr = std::unique_ptr<sf::Shape>;

class ShapeRenderer : public Component
{
  Shape_ptr m_shape;
  sf::Vector2f m_half_bounds;

 public:
  void update(GameObject&) override;
  void draw(GameObject&, sf::RenderWindow&) override;
  template<typename Shape>
  Shape* make_shape();
};

template<typename Shape>
Shape* ShapeRenderer::make_shape()
{
  m_shape         = std::make_unique<Shape>();
  auto bounds     = m_shape->getLocalBounds();
  m_half_bounds.x = 0.5f * bounds.size.x;
  m_half_bounds.y = 0.5f * bounds.size.y;
  return static_cast<Shape*>(m_shape.get());
}
} // namespace isaac
#endif
