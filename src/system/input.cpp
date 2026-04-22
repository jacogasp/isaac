#include "isaac/system/input.hpp"
#include "isaac/system/logger.hpp"
#include "isaac/system/service_locator.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace isaac {

Input::Input()
{
  auto logger = ServiceLocator<Logger>::get_service();
  logger->debug("Input initialized");
}

void Input::on_notify(Observable<sf::Event>& subject, sf::Event const& event)
{
  if (auto key = event.getIf<sf::Event::KeyPressed>()) {
    m_keyboard.at(static_cast<int>(key->code)) = true;
  } else if (auto key = event.getIf<sf::Event::KeyReleased>()) {
    m_keyboard.at(static_cast<int>(key->code)) = false;
  }

  update_axis();
}

void Input::update_axis()
{
  keys_t up_keys    = key_bindings[up];
  keys_t left_keys  = key_bindings[left];
  keys_t down_keys  = key_bindings[down];
  keys_t right_keys = key_bindings[right];

  bool move_up    = false;
  bool move_left  = false;
  bool move_down  = false;
  bool move_right = false;

  for (auto key : up_keys) {
    move_up |= key_pressed(key);
  }
  for (auto key : left_keys) {
    move_left |= key_pressed(key);
  }
  for (auto key : down_keys) {
    move_down |= key_pressed(key);
  }
  for (auto key : right_keys) {
    move_right |= key_pressed(key);
  }

  m_axis.x = 1.0f * (float)move_right - 1.0f * (float)move_left;
  m_axis.y = 1.0f * (float)move_down - 1.0f * (float)move_up;
}

bool Input::key_pressed(sf::Keyboard::Key key)
{
  return m_keyboard.at(static_cast<int>(key));
}

float Input::get_X_axis()
{
  return m_axis.x;
}

float Input::get_Y_axis()
{
  return m_axis.y;
}

sf::Vector2f Input::get_axis()
{
  return m_axis;
}
} // namespace isaac
