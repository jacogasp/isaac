#ifndef ISAAC_DEMO_PARTICLE_HPP
#define ISAAC_DEMO_PARTICLE_HPP

#include "isaac/components/game_object.hpp"
#include "isaac/components/rigidbody_2d.hpp"
#include "isaac/components/shape_renderer.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <cassert>

struct RandomColor : public sf::Color
{
  RandomColor()
  {
    r = std::rand() % 256;
    g = std::rand() % 256;
    b = std::rand() % 256;
    a = 255;
  }
};

class Particle : public isaac::GameObject
{
  isaac::RigidBody2D* m_rigid_body = nullptr;

  void on_start() override
  {
    m_rigid_body =
        &make_component<isaac::RigidBody2D>(isaac::Circle2DShape{10.0f});
    auto& sr    = make_component<isaac::ShapeRenderer>();
    auto& shape = sr.make_shape<sf::CircleShape>(10.0f);
    shape.setFillColor(RandomColor{});
    auto rnd = []() { return static_cast<float>(std::rand() % 100 - 50); };
    set_position({rnd(), rnd()});
  }

 public:
  isaac::RigidBody2D* get_rigid_body() const
  {
    assert(m_rigid_body);
    return m_rigid_body;
  }
};

struct ParticleEvent
{};

#endif // ISAAC_DEMO_PARTICLE_HPP
