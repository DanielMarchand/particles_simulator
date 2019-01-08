#!/bin/env python3
#A few very simple tests to verify correct installation

def test_particlefactory():
    from pypart import ParticlesFactoryInterface
    ParticlesFactoryInterface.getInstance()
    return

def test_planetsfactory():
    from pypart import PlanetsFactory
    PlanetsFactory.getInstance()
    return

def test_pingpongballsfactory():
    from pypart import PingPongBallsFactory
    PingPongBallsFactory.getInstance()
    return

def test_materialpointfactory():
    from pypart import MaterialPointsFactory 
    MaterialPointsFactory.getInstance()
    return
