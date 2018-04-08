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
            plt.plot((x[i*Ny + j], x[(i+1)*Ny + j]),
                     (y[i*Ny + j], y[i*Ny + j]), color='b') 
            plt.plot((x[i*Ny + j], x[(i+1)*Ny + (j+1)]),
                     (y[i*Ny + j], y[(i+1)*Ny + (j+1)]), color='b') 
            plt.plot((x[i*Ny + j], x[i*Ny + (j+1)]),
                     (y[i*Ny + j], y[i*Ny + (j+1)]), color='b')
        elif ((i < Nx-1) and (j == Ny-1)):
            plt.plot((x[i*Ny + j], x[(i+1)*Ny + j]),
                     (y[i*Ny + j], y[i*Ny + j]), color='b')
        elif ((i == Nx-1) and (j < Ny-1)):
            plt.plot((x[i*Ny + j], x[i*Ny + j+1]),
                     (y[i*Ny + j], y[i*Ny + j+1]), color='b') 
            
plt.scatter(x, y)
plt.axis('equal')
plt.show()
# plt.savefig("grid_{}_{}.png".format(Nx,Ny))
