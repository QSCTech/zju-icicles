#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
# Build a vector of 10000 normal deviates with variance 0.5^2 and mean 2

mu, sigma = 2, 0.5
v = np.random.normal(mu,sigma,10000)

# Plot a normalized histogram with 50 bins

plt.hist(v, bins=50, normed=1)       # matplotlib version (plot)
plt.grid(True)
plt.show()

# Compute the histogram with numpy and then plot it
(n, bins) = np.histogram(v, bins=50, normed=True)  # NumPy version (no plot)
plt.plot(.5*(bins[1:]+bins[:-1]), n)
y = mlab.normpdf(bins, mu, sigma)
plt.plot(bins, y, 'r--', linewidth=1)
plt.grid(True)
plt.show()
