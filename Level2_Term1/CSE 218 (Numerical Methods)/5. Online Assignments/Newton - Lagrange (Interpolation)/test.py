import numpy as np


def newtonInterp_coefficient(arrX, arrY):
    m = len(arrX)

    arrX = np.copy(arrX)
    a = np.copy(arrY)
    for k in range(1, m):
        a[k:m] = (a[k:m] - a[k - 1]) / (arrX[k:m] - arrX[k - 1])
        print(a)


x = [10, 15, 20, 22.5]
y = [227.4, 362.78, 517.35, 602.97]
print(y)
newtonInterp_coefficient(x, y)
