#!/bin/env python3
#A few very simple tests to verify correct installation
import tempfile
from pypart import ComputeTemperature                                                                             
from pypart import MaterialPointsFactory 

#NOTE we can only test one factory method at a time
#def test_particlefactory():
#    from pypart import ParticlesFactoryInterface
#    factory =ParticlesFactoryInterface.getInstance()
#    del factory
#    return
#
#def test_planetsfactory():
#    from pypart import PlanetsFactory
#
#    factory = PlanetsFactory.getInstance()
#
#    f = tempfile.NamedTemporaryFile()
#    evol = factory.createSimulation(f.name, float(1.1), bool(True))
#    del factory
#    return
#
#def test_pingpongballsfactory():
#    from pypart import PingPongBallsFactory
#
#    factory = PingPongBallsFactory.getInstance()
#
#    f = tempfile.NamedTemporaryFile()
#    evol = factory.createSimulation(f.name, float(1.1), bool(True))
#    del factory
#    return

def createComputes(self, timestep):                          
    compute_temp = ComputeTemperature()                      
    compute_temp.conductivity = 1                            
    compute_temp.L = 2                                     
    compute_temp.capacity = 1                                
    compute_temp.density = 1                                 
    compute_temp.deltat = 1                                  
    print(compute_temp)
    self.system_evolution.addCompute(compute_temp)           
    return

def test_materialpointfactory():
    factory = MaterialPointsFactory.getInstance()

    f = tempfile.NamedTemporaryFile()
    evol = factory.createSimulation(f.name, float(1.1), createComputes)
    del factory
    return



