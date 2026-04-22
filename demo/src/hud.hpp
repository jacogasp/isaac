#ifndef ISAAC_DEMO_HUD_HPP
#define ISAAC_DEMO_HUD_HPP

#include "particle.hpp"

#include <isaac/components/game_object.hpp>
#include <isaac/system/observer.hpp>
#include <imgui.h>

enum class HudEventType
{
  SPAWN_RATE_CHANGED,
  RESTITUTION_CHANGED,
};

struct HudEvent
{
  HudEventType type;
  float value;
};

class Hud
    : public isaac::GameObject
    , public isaac::Observer<ParticleEvent>
    , public isaac::Observable<HudEvent>
{
  int m_counter       = 0;
  float m_spawn_rate  = 1.f;
  float m_restitution = 0.f;

 public:
  void on_draw(sf::RenderWindow&) override
  {
    float spawn_rate  = m_spawn_rate;
    float restitution = m_restitution;

    ImGui::Begin("Inspector");
    ImGui::Text("Particles: %d", m_counter);
    ImGui::SliderFloat("spawning rate", &spawn_rate, 1.f, 25.0f);
    ImGui::SliderFloat("restitution", &restitution, 0.f, 2.f);
    ImGui::End();

    if (std::abs(spawn_rate - m_spawn_rate) > 0.01f) {
      m_spawn_rate = spawn_rate;
      HudEvent event{HudEventType::SPAWN_RATE_CHANGED, m_spawn_rate};
      notify(event);
    }

    if (std::abs(restitution - m_restitution) > 0.01f) {
      m_restitution = restitution;
      HudEvent event{HudEventType::RESTITUTION_CHANGED, m_restitution};
      notify(event);
    }
  };

  void on_notify(isaac::Observable<ParticleEvent>& subject,
                 ParticleEvent const& event) override
  {
    ++m_counter;
  }
};

#endif // ISAAC_DEMO_HUD_HPP
