#!/usr/bin/env python
import numpy as np
import pandas as pd
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("resolution", help="resolution of the grid of NxN grid", type=int)
#parser.add_argument("heat_form", help="form of the heat applied")
parser.add_argument("radius", help="radius over which heat will be applied")
parser.add_argument("filename", help="name of generated input file")

args = parser.parse_args()
resolution = args.resolution
R = float(args.radius)
#heat_form = args.heat_form
file_name = args.filename

L = 1 # the box has a domain of [-L, L] over x and y
num_particles = resolution ** 2
particles_df = pd.DataFrame(np.zeros((num_particles, 3)), columns=["x","y", "T"])

particles_df['i'] = (particles_df.index % resolution)
particles_df['j'] = np.floor(particles_df.index / resolution)
particles_df['x'] = -L + 2*particles_df['i']*(L/resolution)
particles_df['y'] = -L + 2*particles_df['j']*(L/resolution)
particles_df.drop(columns=['i','j'], inplace=True)

#NOTE can use the following code to apply a 'strip' of heat
## two line heat source
#is_power_of_two = (np.log2(resolution) == int(np.log2(resolution)))
#if not is_power_of_two:
#    print("Can only use this heat type if a power of two")
#particles_df['h'] = np.where(particles_df["x"] == 0.5, 1, 0)

# circular heat source
particles_df['h'] = np.where(particles_df["x"]**2 + particles_df['y']**2 < R, 1, 0)
file_data = particles_df.get_values()

np.savetxt(args.filename, file_data, delimiter=" ")
