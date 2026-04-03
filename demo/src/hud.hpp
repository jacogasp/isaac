#ifndef ISAAC_DEMO_HUD_HPP
#define ISAAC_DEMO_HUD_HPP

#include <isaac/objects/ui/canvas.hpp>
#include <imgui.h>

#include <iostream>

class Hud : public isaac::Canvas
{
 public:
  void on_draw() override
  {
    ImGui::ShowDemoWindow();
    ImGui::Begin("Hello, World!");
    if (ImGui::Button("Click me!")) {
      std::cout << "Hellooo!\n";
    }
    ImGui::End();
  };
};

#endif // ISAAC_DEMO_HUD_HPP
