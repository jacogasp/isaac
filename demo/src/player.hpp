#ifndef ISAAC_DEMO_PLAYER_HPP
#define ISAAC_DEMO_PLAYER_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <isaac/components/game_object.hpp>
#include <isaac/components/rigidbody_2d.hpp>
#include <isaac/components/shape_renderer.hpp>
#include <isaac/physics/collision_shape_2d.hpp>
#include <isaac/system/input.hpp>
#include <isaac/system/logger.hpp>
#include <isaac/system/service_locator.hpp>

#include "orbiter.hpp"

class Player : public isaac::GameObject
{
  void on_start() override
  {
    // components
    auto shape_renderer = make_component<isaac::ShapeRenderer>();
    auto& shape         = shape_renderer->make_shape<sf::CircleShape>(25.0f);
    shape.setFillColor({255, 255, 0});

    auto rigid_body =
        make_component<isaac::RigidBody2D>(isaac::Circle2DShape{25.0f});

    // children
    auto orbiter = make_child<Orbiter>();
    orbiter->set_attractor(*this);
    set_position({400 - shape.getRadius(), 300 - shape.getRadius()});
  }

  void on_update(float delta) override
  {
    // assert(m_rigid_body);
    // auto position = get_position();
    // auto axis     = isaac::Input::get_axis();
    // auto force    = 300.0f * delta * isaac::vec2{axis.x, axis.y};
    // m_rigid_body->set_velocity(force);
  }

  void on_draw(sf::RenderWindow& window) override
  {
    sf::RectangleShape h{{1, 600}};
    h.setPosition({400, 0});
    sf::RectangleShape v{{800, 1}};
    v.setPosition({0, 300});
    window.draw(h);
    window.draw(v);
  }

  void on_collision_2d(isaac::Collision2D const& collision) override
  {
    auto logger = isaac::ServiceLocator<isaac::Logger>::get_service();
    logger->info("There was a collision!");
    // if (collision.other->game_object()) {
    //   collision.other->game_object()->destroy();
    // }
  }
};

#endif // ISAAC_DEMO_PLAYER_HPP
