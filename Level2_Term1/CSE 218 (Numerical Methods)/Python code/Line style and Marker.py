import numpy as np
import matplotlib.pyplot as plt

plt.close('all')
x=np.linspace(-2*np.pi,2*np.pi,100)
sinx=np.sin(x)


plt.plot(x, sinx, color='m',
linestyle='-.', linewidth=4,
marker='o', markerfacecolor='k', markeredgecolor='g',
markeredgewidth=3, markersize=5,
label='sin')


plt.legend(loc="best")
plt.grid()
plt.xlabel("Radian")
plt.ylabel("Amplitude")

plt.show()
