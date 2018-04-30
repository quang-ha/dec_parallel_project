import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import itertools

# Read in string
N = [20, 50, 100]
sigma = [0, 0.1, 0.2]

coordVals = []
eigVals = []

marker = itertools.cycle(('o', 'v', '^', 'h', 'd', 'p'))
colors = cm.brg(np.linspace(0, 1, len(N)))


fig = plt.figure(figsize=(10, 8))
ax = plt.subplot(111)

# Create the graph
for n in range(len(N)):
    for i in range(len(sigma)):
        # Read in eigen value
        eigFile = 'eigVals_{}_{}_{}.dat'.format(N[n], N[n], sigma[i])
        # Ratio offset
        ratio = np.sqrt(3)
        eig_data = np.loadtxt(eigFile, skiprows=1)
        eig_data = ((ratio*N[n]/N[0])**2)*eig_data[::-1]
        # Plot it
        ax.plot(range(len(eig_data)), eig_data, label=r'$N$={}, $\sigma$={}'.format(N[n], sigma[i]),
                marker=next(marker), markersize=8, lw=0.01, color=colors[n])    

# Label and add grids, legends
ax.set_xlabel('Eigennumber')
ax.set_ylabel('Eigenvalue')
ax.grid()
ax.legend(loc=4)

# Shrink current axis by 20%
box = ax.get_position()
ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])

# Put a legend to the right of the current axis
ax.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.savefig("noise_N_converge.png")
