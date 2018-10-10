import numpy as np
import scipy.optimize

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm


import sys

def ex_function(xy):
    x = np.array(xy[0])
    y = np.array(xy[1])
    S_xy = 2.*x**2. + (3./2.)*y**2. +x*y - x - 2.*y + 6.
    return S_xy

def callback(*args, **kwargs):
    global xyz
    xy = args[0]
    x, y, z = xy[0], xy[1], ex_function(xy)
    xyz.append([x,y,z])

def optimize_function(func, start, **kwargs):
    global xyz
    xyz=[]
    scipy.optimize.minimize(ex_function,
                        np.array(start),
                        tol=1e-9,
                        callback=callback, **kwargs)
    return xyz

def gen_surface_plot(func, ax):
    x = y = np.arange(-5.0, 5.0, 0.05) #may wish to abstract the grid out
    X, Y = np.meshgrid(x, y)
    zs = np.array([ex_function([x,y]) for x,y in zip(np.ravel(X), np.ravel(Y))])
    Z = zs.reshape(X.shape)

    ax.plot_surface(X, Y, Z,  cmap=cm.viridis, shade=False, alpha=0.45)#cmap=cm.viridis)
    ax.contour(X,Y,Z, colors='k')
    return ax

def gen_3D_plot(xyz, ax, **kwargs):
    x = [val[0] for val in xyz]
    y = [val[1] for val in xyz]
    z = [val[2] for val in xyz]
    ax.plot3D(x, y, z, **kwargs)
    return ax

if __name__ == "__main__":
  if len(sys.argv) != 2:
    sys.exit("optimize.py <output file path>")

  output_file = str(sys.argv[1])

  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  ax = gen_surface_plot(ex_function, ax)
  start_position = [5,5]


  method="BFGS"
  xyz = optimize_function(ex_function, start_position, method=method)
  xyz.insert(0,[start_position[0], start_position[1], ex_function(start_position)])
  ax = gen_3D_plot(xyz, ax,
                   linestyle='--', c='r', marker='o', mfc='none', label=method)

  method="CG"
  xyz = optimize_function(ex_function, start_position, method=method)
  xyz.insert(0,[start_position[0], start_position[1], ex_function(start_position)])
  ax = gen_3D_plot(xyz, ax,
                   linestyle='--', c='b', marker='o', mfc='none', label=method)


  ax.set_xlabel('X')
  ax.set_ylabel('Y')
  ax.set_zlabel('Z')
  ax.grid(b=False)

  plt.legend()
  plt.savefig(output_file)
