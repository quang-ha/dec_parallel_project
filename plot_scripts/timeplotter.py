# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

plt.rcParams['figure.figsize'] = 16, 12

data1 = np.loadtxt('../testdata/Scalar_EigTimes_O3_ffast.txt')
data2 = np.loadtxt('../testdata/Scalar_EigTimes_O3_ffast_openmp.txt')
# data3 = np.loadtxt('Scalar_EigTimes.txt')
# print(data)
#plt.plot(data[:, 0], np.mean(data[:, 1:], axis=1))
sns.tsplot(data1[:, 1:].T, time=data1[:, 0]**2, color='blue', ci=[68, 95], condition='Serial') # Transpose because (units, time)
sns.tsplot(data2[:, 1:].T, time=data2[:, 0]**2, color='green', ci=[68, 95], condition='OpenMP') # Transpose because (units, time)
# sns.tsplot(data3[:, 1:].T, time=data3[:, 0], color='indigo') # Transpose because (units, time)

plt.xlabel('Problem size')
plt.ylabel('Time in seconds')
# plt.legend(['Serial 0.95 ci', 'Serial 0.68 ci', 'OpenMP 0.95 ci', 'OpenMP 0.68 ci'])
plt.title('-O3 -ffast-math')
plt.show()

data1 = np.loadtxt('../testdata/Scalar_EigTimes_O3.txt')
data2 = np.loadtxt('../testdata/Scalar_EigTimes_O3_openmp.txt')
#data3 = np.loadtxt('Scalar_EigTimes_O2.txt')
# print(data)
#plt.plot(data[:, 0], np.mean(data[:, 1:], axis=1))
sns.tsplot(data1[:, 1:].T, time=data1[:, 0]**2, color='blue', ci=[68, 95], condition='Serial') # Transpose because (units, time)
sns.tsplot(data2[:, 1:].T, time=data2[:, 0]**2, color='green', ci=[68, 95], condition='OpenMP')
#sns.tsplot(data3[:, 1:].T, time=data3[:, 0], color='indigo') # Transpose because (units, time)

plt.xlabel('Problem size')
plt.ylabel('Time in seconds')
# plt.legend(['Serial 0.95 ci', 'Serial 0.68 ci', 'OpenMP 0.95 ci', 'OpenMP 0.68 ci'])
plt.title('-O3')
plt.show()

data1 = np.loadtxt('../testdata/Scalar_EigTimes_O2.txt')
data2 = np.loadtxt('../testdata/Scalar_EigTimes_O2_openmp.txt')
#data3 = np.loadtxt('Scalar_EigTimes_O2.txt')
# print(data)
#plt.plot(data[:, 0], np.mean(data[:, 1:], axis=1))
sns.tsplot(data1[:, 1:].T, time=data1[:, 0]**2, color='blue', ci=[68, 95], condition='Serial') # Transpose because (units, time)
sns.tsplot(data2[:, 1:].T, time=data2[:, 0]**2, color='green', ci=[68, 95], condition='OpenMP')
#sns.tsplot(data3[:, 1:].T, time=data3[:, 0], color='indigo') # Transpose because (units, time)

plt.xlabel('Problem size')
plt.ylabel('Time in seconds')
# plt.legend(['Serial 0.95 ci', 'Serial 0.68 ci', 'OpenMP 0.95 ci', 'OpenMP 0.68 ci'])
plt.title('-O2')
plt.show()