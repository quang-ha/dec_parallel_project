import numpy as np
import matplotlib.pyplot as plt

# Read in string
sigma = [0, 0.025, 0.05, 0.075,
         0.1, 0.2, 0.5, 0.75]

coordVals = []
eigVals = []

# Create the graph
nrow = 4; ncol = 4;
fig, axs = plt.subplots(figsize=(16, 9),
                        nrows=nrow, ncols=ncol, squeeze=0) 
axs = axs.reshape(-1)

for i in range(len(sigma)):
    coordFile = 'coords_{}.dat'.format(sigma[i])
    eigFile = 'eigVals_{}.dat'.format(sigma[i])

    # Read in data
    data = np.loadtxt(coordFile, skiprows=2)
    Nx, Ny = int(data[0, 0]), int(data[0, 1])
    x, y = data[1:, 0], data[1:, 1]
    axs[i*2].triplot(x, y)
    axs[i*2].scatter(x, y)
    axs[i*2].axis('equal')
    axs[i*2].axis('off')
    
    # Ratio offset
    ratio = np.sqrt(3)
    eig_data = np.loadtxt(eigFile, skiprows=1)
    eig_data = eig_data[::-1]
    eigVals.append(eig_data)
    axs[i*2+1].scatter(np.linspace(1, len(eig_data), len(eig_data)),
                ratio*eig_data)
    axs[i*2+1].set_xlabel("Eigennumber")
    axs[i*2+1].set_ylabel("Eigenvalues")
    axs[i*2+1].set_title("{}".format(sigma[i]))

plt.tight_layout()
plt.savefig("graph_eigvals.png")

plt.figure(figsize=(10, 8))
# Obtain the L2 norm - full spectrum
N = len(eigVals[0])

for p in np.arange(10, 110, 10):
    fp = p/100.0
    eigL2 = []
    # Collect the norm
    for i in range(len(sigma)):
        eigL2.append((1.0/N)*np.linalg.norm(eigVals[i][:(int)(fp*N)] -
                                            eigVals[0][:(int)(fp*N)]))
    # Plot the line
    plt.semilogy(sigma, eigL2, '-*', lw=2.0, label="{}% spectrum".format(p))

plt.xlabel(r'$\frac{\Delta l}{l}$')
plt.ylabel(r'L2 norm')
plt.legend()
plt.savefig("L2_sigma.png")

