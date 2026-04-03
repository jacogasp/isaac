cmake_minimum_required(VERSION 3.20)

if (NOT DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  message(FATAL_ERROR "You must set VCPKG_ROOT env variable or pass CMAKE_TOOLCHAIN_FILE")
endif()

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(Isaac VERSION 0.1.0)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)


add_library(libisaac
  src/isaac.cpp
  src/components/collider_2d.cpp
  src/components/component.cpp
  src/components/game_object.cpp
  src/components/sprite_renderer.cpp
  src/internal/base_object.cpp
  src/objects/ui/canvas.cpp
  src/physics/collision_2d.cpp
  src/physics/collision_shape_2d.cpp
  src/physics/geometry_2d.cpp
  src/physics/math.cpp
  src/physics/matrix.cpp
  src/physics/physics_2d.cpp
  src/physics/utility.cpp
  src/physics/vector.cpp
  src/render/window_server.cpp
  src/scene/scene.cpp
  src/scene/scene_manager.cpp
  src/system/cyclic_iterator.cpp
  src/system/defaults.cpp
  src/system/input.cpp
  src/system/logger.cpp
  src/system/observer.cpp
  src/system/random.cpp
  src/system/service_locator.cpp
  src/system/thread.cpp
  src/system/world.cpp
)

add_library(isaac::isaac ALIAS libisaac)

set_target_properties(libisaac PROPERTIES
  OUTPUT_NAME Issac
  EXPORT_NAME isaac
)

add_subdirectory(tests)


target_link_libraries(libisaac SFML::Graphics SFML::Window SFML::System)
target_include_directories(libisaac PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

install(
  TARGETS libisaac
  EXPORT IsaacTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

install(EXPORT IsaacTargets
  FILE IsaacTargets.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Isaac
  NAMESPACE isaac::
)

# Use a standard helper module for packaging
include(CMakePackageConfigHelpers)

# Generate the main Config file from our template
configure_package_config_file(
  "cmake/IsaacConfig.cmake.in"
  "IsaacConfig.cmake"
  INSTALL_DESTINATION
  "${CMAKE_INSTALL_LIBDIR}/cmake/Isaac"
)

# Generate a version file for version checking
write_basic_package_version_file(
  "IsaacConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Install the generated config and version files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/IsaacConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/IsaacConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/Isaac"
)

add_subdirectory(demo)
