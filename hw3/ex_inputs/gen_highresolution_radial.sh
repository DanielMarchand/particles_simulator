#!/usr/bin/env sh
OUTPUTFILE=radial_heat_highresolution.txt

if [ -f $OUTPUTFILE ]; then
 echo $OUTPUTFILE already exists!
fi

RESOLUTION=128 #RESOLUTION of 512 is very challenging to render on paraview
RADIUS=0.1
../src/generate_heatequation.py $RESOLUTION $RADIUS $OUTPUTFILE
