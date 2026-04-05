#include "isaac/components/shape_renderer.hpp"
#include "isaac/components/game_object.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>

namespace isaac {

void ShapeRenderer::update(GameObject& game_object)
{
  auto const position = game_object.get_position();
  m_shape->setPosition(sf::Vector2{position.x, position.y} - m_half_bounds);
}

void ShapeRenderer::draw(GameObject& game_object, sf::RenderWindow& window)
{
  window.draw(*m_shape);
}
} // namespace isaac
