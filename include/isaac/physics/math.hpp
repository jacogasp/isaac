#ifndef PHYSICS_MATH_HPP
#define PHYSICS_MATH_HPP

#include <algorithm>
#include <cmath>
#include <limits>

namespace isaac {

// Absolute and relative tolerance https://realtimecollisiondetection.net/
template<typename T>
inline bool cmp(T x, T y)
{
  return std::abs(x - y)
      <= std::numeric_limits<T>::epsilon()
             * std::fmax(static_cast<T>(1),
                         std::fmax(std::abs(x), std::abs(y)));
}

template<typename T>
inline constexpr T clamp(T val, T min, T max)
{
  return std::min(std::max(val, min), max);
}
} // namespace isaac

#endif