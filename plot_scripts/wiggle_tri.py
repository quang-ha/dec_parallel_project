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

r = 0.15
N = 2
angles = []

# Plotting graph
plt.gca()
plt.scatter(A[0], A[1], s=50, marker='o', color='r')
plt.scatter(B[0], B[1], s=50, marker='o', color='r')
plt.scatter(C[0], C[1], s=50, marker='o', color='r')
t = plt.Polygon([A, B, C], fill=False, edgecolor='r', linestyle='--', alpha=0.65, linewidth=2)
plt.gca().add_patch(t)

colors = itertools.cycle(cm.hsv(np.linspace(0, 1, N*N*N)))

for thetaA in np.linspace(0.0, (1.0/3.0)*2.0*np.pi, N):
    for thetaB in np.linspace((1.0/3.0)*2.0*np.pi, (2.0/3.0)*2.0*np.pi, N):
        for thetaC in np.linspace((2.0/3.0)*2.0*np.pi, 2.0*np.pi, N):
            A1, B1, C1 = wiggle(r, thetaA, thetaB, thetaC, A, B, C)
            plt.scatter(A1[0], A1[1], s=15, marker='o', color='b')
            plt.scatter(B1[0], B1[1], s=15, marker='o', color='b')
            plt.scatter(C1[0], C1[1], s=15, marker='o', color='b')
            t = plt.Polygon([A1, B1, C1], fill=False, edgecolor='b')
            plt.gca().add_patch(t)
            # angles.extend(get_angles(A1, B1, C1))

plt.gca().add_patch(plt.Circle(A, r, alpha=0.4, color='r', edgecolor='r'))
plt.gca().add_patch(plt.Circle(B, r, alpha=0.4, color='r', edgecolor='r'))
plt.gca().add_patch(plt.Circle(C, r, alpha=0.4, color='r', edgecolor='r'))
plt.axis('equal')
plt.axis('off')

plt.xlim(-0.5, 1.5)
plt.ylim(-0.5, 1.5)
plt.tight_layout()
plt.savefig("wiggle_schematic.png")

# # histogram of data
# n, bins, patches = plt.hist(angles, 50, density=True, facecolor='g', alpha=0.75)
