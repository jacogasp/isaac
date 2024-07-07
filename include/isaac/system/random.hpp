#ifndef SYSTEM_RANDOM_HPP
#define SYSTEM_RANDOM_HPP

#include <random>

namespace isaac {
class RandomGenerator
{

 public:
  static std::mt19937 s_mt_rand;
  static float range(float min, float max);
};

} // namespace isaac

#endif