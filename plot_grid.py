import numpy as np
import matplotlib.pyplot as plt

# Read in data
data = np.loadtxt("coords.dat", skiprows=2)
Nx, Ny = int(data[0, 0]), int(data[0, 1])
x, y = data[1:, 0], data[1:, 1]

# Draw lines
for i in range(Nx):
    for j in range(Ny):
        if ((i < Nx-1) and (j < Ny-1)):
            plt.plot((x[i*Nx + j], x[(i+1)*Nx + j]),
                     (y[i*Nx + j], y[i*Nx + j]), color='b') 
            plt.plot((x[i*Nx + j], x[(i+1)*Nx + (j+1)]),
                     (y[i*Nx + j], y[(i+1)*Nx + (j+1)]), color='b') 
            plt.plot((x[i*Nx + j], x[i*Nx + (j+1)]),
                     (y[i*Nx + j], y[i*Nx + (j+1)]), color='b')
        elif ((i < Nx-1) and (j == Ny-1)):
            plt.plot((x[i*Nx + j], x[(i+1)*Nx + j]),
                     (y[i*Nx + j], y[i*Nx + j]), color='b')
        elif ((i == Nx-1) and (j < Ny-1)):
            plt.plot((x[i*Nx + j], x[i*Nx + j+1]),
                     (y[i*Nx + j], y[i*Nx + j+1]), color='b') 
            
plt.scatter(x, y)
plt.axis('equal')
plt.savefig("grid_{}_{}.png".format(Nx,Ny))
