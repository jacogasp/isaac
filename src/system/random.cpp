#include "system/random.hpp"

namespace isaac {
static std::random_device random_device{};
std::mt19937 RandomGenerator::s_mt_rand{random_device()};

float RandomGenerator::range(float min, float max)
{
  auto dist = std::uniform_real_distribution<>(min, max);
  return dist(s_mt_rand);
}
} // namespace isaac