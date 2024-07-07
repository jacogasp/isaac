#ifndef SYSTEM_INPUT_HPP
#define SYSTEM_INPUT_HPP

#include "physics/vector.hpp"
#include "system/observer.hpp"

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

#include <array>
#include <unordered_map>
#include <vector>

namespace isaac {

using keyboard_t = std::array<bool, sf::Keyboard::KeyCount>;
using keys_t     = std::vector<sf::Keyboard::Key>;

class Input : public Observer<sf::Event>
{
  inline static keyboard_t m_keyboard;
  inline static vec2 m_axis;

  enum Action
  {
    up,
    left,
    down,
    right,
    jump
  };

  inline static std::unordered_map<Action, keys_t> key_bindings{
      {up, {sf::Keyboard::Up, sf::Keyboard::W}},
      {left, {sf::Keyboard::Left, sf::Keyboard::A}},
      {down, {sf::Keyboard::Down, sf::Keyboard::S}},
      {right, {sf::Keyboard::Right, sf::Keyboard::D}},
      {jump, {sf::Keyboard::Space}},
  };

  void on_notify(Observable<sf::Event>& subject,
                 sf::Event const& event) override;

  static void update_axis();

 public:
  [[nodiscard]] static bool key_pressed(sf::Keyboard::Key key);
  [[nodiscard]] static float get_X_axis();
  [[nodiscard]] static float get_Y_axis();
  [[nodiscard]] static vec2 get_axis();
};
} // namespace isaac
#endif
