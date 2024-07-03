cmake_minimum_required(VERSION 3.20)

if (NOT DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(FATAL_ERROR "You must set VCPKG_ROOT env variable or pass CMAKE_TOOLCHAIN_FILE")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(Isaac)
set(CMAKE_CXX_STANDARD 20)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_library(isaac
  src/defaults.cpp
  src/game.cpp
  src/game_object.cpp
  src/physics/geometry_2d.cpp
  src/physics/math.cpp
  src/physics/matrix.cpp
  src/physics/vector.cpp
  src/system/cyclic_iterator.cpp
  src/system/thread.cpp
)

add_subdirectory(tests)

target_link_libraries(isaac sfml-graphics)
target_include_directories(isaac PUBLIC include/isaac)

add_subdirectory(demo)
