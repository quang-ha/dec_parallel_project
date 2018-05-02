import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import itertools

# Read in string
N = [20, 50, 100, 200, 250]
sigma = [0.05, 0.08, 0.1]

coordVals = []
eigVals = []

marker = itertools.cycle(('o', 'v', '^', 'h', 'd', 'p'))
colors = cm.jet(np.linspace(0, 1, len(N)))

fig, axs = plt.subplots(1, 3, figsize=(30, 8), edgecolor='k')
axs = axs.ravel()

# Create the graph
for i in range(len(sigma)):
    for n in range(len(N)):
        # Read in eigen value
        eigFile = 'eigVals_{}_{}_{}.dat'.format(N[n], N[n], sigma[i])
        # Ratio offset
        ratio = np.sqrt(3)
        eig_data = np.loadtxt(eigFile, skiprows=1)
        eig_data = ((ratio*N[n]/N[0])**2)*eig_data[::-1]
        # Plot it
        axs[i].plot(range(len(eig_data)), eig_data, label=r'$N$={}'.format(N[n]),
                    marker=next(marker), markersize=8, lw=0.01, color=colors[n])    

    # Label and add grids, legends
    axs[i].set_xlabel('Eigennumber')
    axs[i].set_ylabel('Eigenvalue')
    axs[i].grid()
    axs[i].legend(loc=4)
    axs[i].set_title(r'$\sigma$={}'.format(sigma[i]))

plt.tight_layout()
plt.savefig("noise_converge_3.png")
