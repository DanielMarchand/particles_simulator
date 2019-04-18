#!/usr/bin/env python

import sys
import argparse
from pypart import MaterialPointsFactory, ParticlesFactoryInterface
from pypart import PingPongBallsFactory, PlanetsFactory
from pypart import CsvWriter
from pypart import ComputeTemperature
# help(pypart)

parser = argparse.ArgumentParser(description='Particles code')
parser.add_argument('nsteps', type=int,
                    help='specify the number of steps to perform')
parser.add_argument('freq', type=int,
                    help='specify the frequency for dumps')
parser.add_argument('filename', type=str,
                    help='start/input filename')
parser.add_argument('particle_type', type=str,
                    help='particle type (ping_pong or planet)')
parser.add_argument('timestep', type=float,
                    help='timestep')

args = parser.parse_args()
nsteps = args.nsteps
freq = args.freq
filename = args.filename
particle_type = args.particle_type
timestep = args.timestep

if particle_type == "planet":
    PlanetsFactory.getInstance()
elif particle_type == "ping_pong":
    PingPongBallsFactory.getInstance()
elif particle_type == "material_point":
    MaterialPointsFactory.getInstance()
else:
    print("Unknown particle type: ", particle_type)
    sys.exit(-1)

factory = ParticlesFactoryInterface.getInstance()


def createComputes(self, timestep):
    compute_temp = ComputeTemperature()
    compute_temp.conductivity = 1
    # TODO: adjust c++ code to have length property
    # compute_temp.L = 2
    compute_temp.capacity = 1
    compute_temp.density = 1
    compute_temp.deltat = 1
    self.system_evolution.addCompute(compute_temp)


evol = factory.createSimulation(filename, timestep, createComputes)

dumper = CsvWriter("init.csv")
dumper.write(evol.getSystem())

evol.setNSteps(nsteps)
evol.setDumpFreq(freq)
evol.evolve()
