#include "isaac/components/shape_renderer.hpp"
#include "isaac/components/game_object.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <cassert>

namespace isaac {

void ShapeRenderer::update(GameObject& game_object)
{
  auto const go_pos = game_object.get_global_position();
  for (auto&& shape : m_shapes) {
    std::visit([&](auto& s) { s.setPosition(go_pos); }, shape);
  }
  m_last_position = go_pos;
}

void ShapeRenderer::draw(GameObject& _, sf::RenderWindow& window)
{
  for (auto&& shape : m_shapes) {
    std::visit([&](auto& s) { window.draw(s); }, shape);
  }
}
} // namespace isaac
