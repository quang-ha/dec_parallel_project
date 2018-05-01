import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import itertools

def side(x1, x2):
    return np.linalg.norm(x1-x2)

def get_angles(A, B, C):
    c, b, a = side(A, B), side(A, C), side(B, C)
    angs = []
    angs.append(np.degrees(np.arccos((a*a + b*b - c*c)/(2.0*a*b))))
    angs.append(np.degrees(np.arccos((b*b + c*c - a*a)/(2.0*b*c))))
    angs.append(np.degrees(np.arccos((c*c + a*a - b*b)/(2.0*c*a))))
    
    return angs

def wiggle(r, tA, tB, tC, _A, _B, _C):
    _A1 = _A + r*np.array([np.cos(tA), np.sin(tA)])
    _B1 = _B + r*np.array([np.cos(tB), np.sin(tB)])
    _C1 = _C + r*np.array([np.cos(tC), np.sin(tC)])

    return _A1, _B1, _C1

# Points of equilateral triangles
A = np.array([0.0, 0.0])
B = np.array([1.0, 0.0])
C = np.array([0.5, 0.5*np.sqrt(3)])

# R = [0.01, 0.02, 0.05, 0.08, 0.10, 0.20, 0.30, 0.40]
R = np.linspace(0.01, 0.45, 80)
N = 50

# # Create subplot
# fig, axs = plt.subplots(2, 4, figsize=(20, 10), edgecolor='k')
# axs = axs.ravel()

num_90 = []
for i in range(len(R)):
    r = R[i]
    angles = []
    for thetaA in np.linspace(0.0, 2.0*np.pi, N):
        for thetaB in np.linspace(0.0, 2.0*np.pi, N):
            for thetaC in np.linspace(0.0, 2.0*np.pi, N):
                A1, B1, C1 = wiggle(r, thetaA, thetaB, thetaC, A, B, C)
                angles.extend(get_angles(A1, B1, C1))
    num_90.append(100*sum(i>=90.00 for i in angles)/len(angles))

plt.figure(figsize=(6, 6))
plt.xlabel(r'$\sigma$')
plt.ylabel('Percentage of angles greater than 90 degree (%)')
plt.plot(R, num_90)
plt.savefig('percentage_sigma.png')
    
#     # histogram of data
#     n, bins, patches = axs[i].hist(angles, 50, density=True, facecolor='g', alpha=0.75)
#     axs[i].axvline(x=90.0, lw=2, color='r', linestyle='--')
#     axs[i].set_xlim(0.0, 180.0)
#     axs[i].set_ylabel('Density')
#     axs[i].set_xlabel('Angles')
#     axs[i].set_title(r'$\sigma$={}'.format(r))
    
# plt.tight_layout()
# plt.savefig('angle_histograms.png')
