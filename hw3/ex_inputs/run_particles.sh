#!/usr/bin/env sh

if [ -d ./dumps ]; then
  rm -rf ./dumps
fi
mkdir dumps

#particles n_timesteps radius output_file particle_type timestep
../src/build/particles 100 1 radial_heat_highresolution.txt material_point 0.001
