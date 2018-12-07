#!/usr/bin/env sh

INPUT_FILE=radial_heat_highresolution.txt

if [ ! -f $INPUT_FILE ]; then
  echo Could not find $INPUT_FILE, consider running gen_highresolution_radial.sh
fi

if [ -d ./dumps ]; then
  rm -rf ./dumps
fi
mkdir dumps

N_TIMESTEPS=100
DUMP_FREQ=10
DELTA_T=0.0001
../src/build/particles $N_TIMESTEPS $DUMP_FREQ $INPUT_FILE material_point $DELTA_T
