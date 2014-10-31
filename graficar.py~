import numpy as np
import matplotlib.pyplot as plt
import pylab
from mpl_toolkits.mplot3d import Axes3D


infile = open('trayectoria_1000_60.dat', 'r')

lines = infile.readlines()

x=np.zeros(np.size(lines))
y=np.zeros(np.size(lines))
z=np.zeros(np.size(lines))

i=0
for line in lines:
    p = line.split()
    x[i]=p[1]
    y[i]=p[2]
    z[i]=p[3]
    i=i+1


#2D Figure
fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("xy_trajectory")
plt.scatter(x,y, label="xy_trajectory")
ax.legend()
filename = 'trajectory_xy'
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()


#3D figure

fig = pylab.figure()
ax = Axes3D(fig)

filename = 'trajectory'
ax.scatter(x,y,z)
plt.savefig(filename + '.pdf',format = 'pdf', transparent=True)
plt.close()

