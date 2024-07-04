#ifndef PHYSICS_UTILITY_HPP
#define PHYSICS_UTILITY_HPP

#include "vector.hpp"
#include <SFML/System.hpp>

namespace isaac {
template<typename T>
sf::Vector2<T> to_sfml(vec2 const& v)
{
  return sf::Vector2<T>{v.x, v.y};
}

template<typename T>
sf::Vector2<T> to_sfml(vec3 const& v)
{
  return sf::Vector3<T>{v.x, v.y, v.z};
}

} // namespace isaac
#endif
