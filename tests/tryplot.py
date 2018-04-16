import numpy as np
import matplotlib.pyplot as plt

a = np.loadtxt('coords.dat', skiprows=3)
# print(a)
plt.rcParams['figure.figsize'] = 5, 3**0.5/2*5
plt.triplot(a[:, 0], a[:, 1])
#plt.xlim([0, 1.5])
#plt.ylim([0, ])
plt.show()
