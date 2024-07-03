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
  std::vector<Shape_ptr> m_shapes{};
  WindowServer* m_window_server;

 public:
  void start() override;
  void update(GameObject&) override;
  template<typename Shape>
  Shape* make_shape();
};

template<typename Shape>
Shape* SpriteRenderer::make_shape()
{
  m_shapes.push_back(std::make_unique<Shape>());
  return static_cast<Shape*>(m_shapes.back().get());
}
} // namespace isaac
#endif
