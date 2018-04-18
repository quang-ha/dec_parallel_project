import numpy as np
import matplotlib.pyplot as plt

# Create figures
plt.figure(figsize=(16, 8))

# Read in data
data = np.loadtxt("coords.dat", skiprows=2)
Nx, Ny = int(data[0, 0]), int(data[0, 1])
x, y = data[1:, 0], data[1:, 1]

# Draw lines on left subplot
plt.subplot(121)
plt.triplot(x, y)
plt.scatter(x, y)
plt.axis('equal')
plt.axis('off')

# Then plot the eigenvalues
plt.subplot(122)
# Ratio offset
ratio = np.sqrt(3)
eigs_data = np.loadtxt("eigVals.dat", skiprows=1)
plt.scatter(np.linspace(1, len(eigs_data), len(eigs_data)),
            ratio*eigs_data[::-1])
plt.xlabel("Eigennumber")
plt.ylabel("Eigenvalues")
# Save figure
plt.savefig("grid_{}_{}.png".format(Nx,Ny))
