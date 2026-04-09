import numpy as np
import matplotlib.pyplot as plt

plt.close('all')
x=np.linspace(-2*np.pi,2*np.pi,100)
sinx=np.sin(x)
plt.plot(x,sinx,label='sin_graph')

plt.legend(loc="best")
plt.grid()
plt.xlabel("Radian")
plt.ylabel("Amplitude")

plt.show()
