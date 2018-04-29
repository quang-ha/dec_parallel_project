import time as t
from subprocess import call

import numpy as np

ns = 15
sizes = np.linspace(10, 180, ns, dtype=np.int32)

numsamples = 10
times = np.zeros([ns, numsamples+1])
for elem, i in enumerate(sizes):
    mean, std = 0, 0
    times[elem, 0] = i
    for sample in range(1, numsamples+1):
        start = t.time()
        call(['./main', f'{i}'])
        elapsed = t.time() - start
        
        times[elem, sample] = elapsed
    print(np.mean(times[elem, 1:]), np.std(times[elem, 1:]))
np.savetxt("Scalar_EigTimes.txt", times, header='SideLen Times ->', fmt='%3.5f')
call(['rm *.dat'])