#!/bin/env python3
#A few very simple tests to verify correct installation
import tempfile 

def test_particlefactory():
    from pypart import ParticlesFactoryInterface
    factory =ParticlesFactoryInterface.getInstance()
    return

def test_planetsfactory():
    from pypart import PlanetsFactory

    factory = PlanetsFactory.getInstance()

    f = tempfile.NamedTemporaryFile()
    evol = factory.createSimulation(f.name, float(1.1), bool(True))
    return

def test_pingpongballsfactory():
    from pypart import PingPongBallsFactory

    factory = PingPongBallsFactory.getInstance()

    f = tempfile.NamedTemporaryFile()
    evol = factory.createSimulation(f.name, float(1.1), bool(True))
    return

def test_materialpointfactory():
    from pypart import MaterialPointsFactory 
    MaterialPointsFactory.getInstance()
    return
