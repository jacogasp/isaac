cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

find_library(isaac ./)
add_executable(isaac-demo 
  src/main.cpp
  src/obstacle.cpp
  src/orbiter.cpp
  src/player.cpp
)
target_link_libraries(isaac-demo PRIVATE isaac)
target_include_directories(isaac-demo PRIVATE ../include)
