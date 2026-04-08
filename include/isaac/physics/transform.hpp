#ifndef ISAAC_PHYSICS_TRANSFORM_HPP
#define ISAAC_PHYSICS_TRANSFORM_HPP

#include <SFML/System/Vector2.hpp>

namespace isaac {

struct Transform {
public:
  sf::Vector2f position{};
  sf::Vector2f global_position{};
};

} // namespace isaac

#endif // ISAAC_PHYSICS_TRANSFORM_HPP
