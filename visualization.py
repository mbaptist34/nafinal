import numpy as np
import scipy as sp

import matplotlib.pyplot as plt

sxcoords = [-1, -0.5, 0.5, 1, 0.5, -0.5, -1.0, -0.5, 0.5, 1.0, 0.5, -0.5]
sycoords = [0, 0.866025, 0.866025, 0, -0.866025, -0.866025, 0, 0.866025, 0.866025, 0, -0.866025, -0.866025]
lxcoords = [-1, -0.6, 0.6, 1, 0.6, -0.6, -1, -0.6, 0.6, 1, 0.6, -0.6]
lycoords = [0, 0.8, 0.8, 0, -0.8, -0.8, 0, 0.8, 0.8, 0, -.8, -.8]


plt.plot(sxcoords, sycoords)
circle = plt.Circle((0, 0), 1, color='r', fill=False)
plt.gcf().gca().add_artist(circle)
plt.show()


plt.plot(lxcoords, lycoords)
plt.plot(sxcoords, sycoords)
circle = plt.Circle((0, 0), 1, color='r', fill=False)
plt.gcf().gca().add_artist(circle)
plt.show()
