#ifndef ISAAC_COMPONENTS_SPRITE_RENDERER_HPP
#define ISAAC_COMPONENTS_SPRITE_RENDERER_HPP

#include "isaac/components/component.hpp"

#include <SFML/Graphics.hpp>
#include <variant>

namespace sf {
class RenderWindow;
}

namespace isaac {

using Shape =
    std::variant<sf::CircleShape, sf::RectangleShape, sf::ConvexShape>;

class ShapeRenderer : public Component
{
  std::vector<Shape> m_shapes;
  sf::Vector2f m_last_position{};

 public:
  void update(GameObject&) override;
  void draw(GameObject&, sf::RenderWindow&) override;

  template<typename S, typename... Args>
  S& make_shape(Args&&... args)
  {
    m_shapes.emplace_back(S{args...});
    return std::get<S>(m_shapes.back());
  }
};
} // namespace isaac
#endif
