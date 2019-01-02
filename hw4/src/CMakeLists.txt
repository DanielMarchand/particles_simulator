cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

################################################################
# libpart
################################################################

add_library(part
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
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  material_points_factory.cc 
  )

add_executable(particles main.cc)
target_link_libraries(particles part)

################################################################
# Pybind11
################################################################
add_subdirectory(pybind11)
#TODO replace with actual pybind module
#pybind11_add_module(pyexample pyexample.cpp)

################################################################
# Google test
################################################################


include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_kepler test_kepler.cc)
target_link_libraries(test_kepler part ${GTEST_BOTH_LIBRARIES} pthread)
gtest_discover_tests(test_kepler)
endif()

################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

# to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
)
add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)

################################################################
# FFTW
################################################################
option(USE_FFT "whether to compile to fft part" ON)

if(USE_FFT)
  set(FFT_LIBRARY_PATH CACHE PATH /usr/lib/x86_64-linux-gnu/)
  find_library (FFT_LIBRARY NAMES "fftw3" PATHS /usr/lib/x86_64-linux-gnu/ ${FFT_LIBRARY_PATH})
  add_library(fft_code compute_temperature.cc)
  target_link_libraries (fft_code ${FFT_LIBRARY})
  target_link_libraries (particles fft_code)
  if (GTEST_FOUND)
    add_executable(test_fft test_fft.cc)
    target_link_libraries(test_fft part fft_code ${GTEST_BOTH_LIBRARIES} ${FFT_LIBRARY} pthread)
    gtest_discover_tests(test_fft)

    add_executable(test_heat_equation test_heat_equation.cc)
    target_link_libraries(test_heat_equation part fft_code ${GTEST_BOTH_LIBRARIES} ${FFT_LIBRARY} pthread)
    gtest_discover_tests(test_fft test_heat_equation)
  endif()
endif()
