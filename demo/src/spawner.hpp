#ifndef ISAAC_DEMO_SPAWNER_HPP
#define ISAAC_DEMO_SPAWNER_HPP

#include "hud.hpp"
#include "particle.hpp"

#include <isaac/components/game_object.hpp>
#include <isaac/system/observer.hpp>

class Spawner
    : public isaac::GameObject
    , public isaac::Observable<ParticleEvent>
    , public isaac::Observer<HudEvent>
{
  float m_elapsed{};
  float m_spawn_interval = 1.f;
  float m_restitution    = 0.f;

  void on_start() override
  {
    set_position({400, 100});
  }

  void on_update(float delta) override
  {
    m_elapsed += delta;
    if (m_elapsed >= m_spawn_interval) {
      spawn();
      m_elapsed = 0.0f;
    }
  }

  void spawn()
  {
    auto child = make_child<Particle>();
    child->get_rigid_body()->set_restitution(m_restitution);
    notify({});
  }

  void on_notify(isaac::Observable<HudEvent>& subject,
                 HudEvent const& event) override
  {
    if (event.type == HudEventType::SPAWN_RATE_CHANGED) {
      m_spawn_interval = 1.0f / event.value;
    } else if (event.type == HudEventType::RESTITUTION_CHANGED) {
      m_restitution = event.value;
    }
  }
};

#endif // ISAAC_DEMO_SPAWNER_HPP
