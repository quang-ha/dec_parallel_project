import numpy as np
import matplotlib.pyplot as plt
import itertools

# Read in string
N = [12, 15, 20, 50, 100, 200]
sigma = [0]

coordVals = []
eigVals = []

marker = itertools.cycle(('o', 'v', '^', 'h', 'd', 'p'))

# Create the graph
for n in range(len(N)):
    for i in range(len(sigma)):
        # Read in eigen value
        eigFile = 'eigVals_{}_{}_{}.dat'.format(N[n], N[n], sigma[i])
        # Ratio offset
        ratio = np.sqrt(3)
        eig_data = np.loadtxt(eigFile, skiprows=1)
        eig_data = ((N[n]/N[0])**2)*ratio*eig_data[::-1]
        # Plot it
        plt.plot(range(len(eig_data)), eig_data, label=r'$N$={}, $\sigma$={}'.format(N[n], sigma[i]),
                 marker=next(marker), markersize=8, lw=0.01)

# Find the polynomial fit for the convergence line
z = np.polyfit(range(len(eig_data)), eig_data, 1)
p = np.poly1d(z)
xp = np.linspace(0, len(eig_data), 1000)
plt.plot(xp, p(xp), '-', alpha=0.5, lw=2.0)

# Label and add grids, legends
plt.xlabel('Eigennumber')
plt.ylabel('Eigenvalue')
plt.grid()
plt.legend(loc=4)
plt.savefig("N_converge.png")
