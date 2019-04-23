# SP4E Project Code
This a collection of the projects created as part of the MATH-611 course 'Scientific programming for Engineers'
Included are the four capstone projects created as part of this course. A brief overview is given
here while for the specifics the 

# Setup
Each directory has its own README which will explain installation for that project. This project requires python3 and the python requirements may
be installed by:
     $pip install -r python_requirements.txt 

The visualization for this project is ideally done using 'paraview'

HW3 & HW4 require the following libraries to be installed:
- fftw3
- googletest
- pybind11 (included as part of hw4-particles_pybind
A robust set of installation environments was not tested but the code has been confirmed to work 
at least on Ubuntu 18.04

# hw1-optimizing 
A simple python script that wraps around the scipy optimize function. Plots the convergence of
both a library optimization function and custom-coded optimization function.

# hw2-intro_cpp_oo 
An introduction to OO programing in C++. This code allows the user to compute a sum-over-N or to
approximate pi to arbitrary precision. 

# hw3-heateqn_fftw 
Simulates a heat transfer equation making use of FFTW3. 
![fftw_heat_ex](https://github.com/DanielMarchand/particles_simulator/blob/master/ex_animations/fftw_heat.gif)


# hw4-heateqn_pybind
Similar to hw3 but with a pybind interface

# hw5-bouncing_particles
Example of the particles code used for bouncing pingpong balls
![bounce_ex](https://github.com/DanielMarchand/particles_simulator/blob/master/ex_animations/bounce.gif)

# Authors
Daniel Marchand (daniel.marchand@epfl.ch)
Ali Falsafi (ali.falsafi@epfl.ch)
