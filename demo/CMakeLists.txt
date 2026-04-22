cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

find_library(isaac ./)
add_executable(isaac-demo
  src/main.cpp
  src/hud.cpp
  src/obstacles.cpp
  src/orbiter.cpp
  src/particle.cpp
  src/player.cpp
  src/spawner.cpp
  src/walls.cpp
)
target_link_libraries(isaac-demo PRIVATE libisaac)
