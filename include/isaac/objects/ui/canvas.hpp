#ifndef ISAAC_OBJECTS_UI_CANVAS_HPP
#define ISAAC_OBJECTS_UI_CANVAS_HPP

#include "isaac/components/game_object.hpp"

namespace isaac {
class Canvas : public GameObject
{
 public:
  virtual void on_draw() {};
};
} // namespace isaac

#endif // ISAAC_OBJECTS_UI_CANVAS_HPP
