cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

add_library(part
  vector.cc
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc)

add_executable(particles main.cc)
target_link_libraries(particles part)

include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_pingpong test_pingpong.cc)
message(${GTEST_LIBRARIES})
target_link_libraries(test_pingpong part ${GTEST_BOTH_LIBRARIES} pthread)
gtest_discover_tests(test_pingpong)
endif()
