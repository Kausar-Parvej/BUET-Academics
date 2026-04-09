import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("dissolveO2.csv", delimiter=",", skip_header=1)
# print(data)
temp_x = np.array([])
temp_y1 = np.array([])
temp_y2 = np.array([])
for row in data:
    temp_x = np.append(temp_x, float(row[0]))
    temp_y1 = np.append(temp_y1, float(row[1]))
    temp_y2 = np.append(temp_y2, float(row[2]))
n = len(temp_x)
# print(temp_x,temp_y1,temp_y2)
x_interp = float(input("Value of X:"))

minimal_pos = n
for i in range(n):

    if x_interp == temp_x[i]:
        print("Value don't need to be interpolated ,it's already given :", temp_y1[i], "and", temp_y2[i])
        exit()
    if x_interp < temp_x[i]:
        minimal_pos = i
        break
order = 4
x = np.array([])
y1 = np.array([])
y2 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        y2 = np.append(y2, temp_y2[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        y2 = np.append(y2, temp_y2[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            y2 = np.append(y2, temp_y2[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            y2 = np.append(y2, temp_y2[right])
            right = right + 1


def error(p, q):
    return abs((p - q) / p) * 100


def newtonInterp_coefficient(arrX, arrY):
    """
    x: list or np array contanining x data points
    y: list or np array contanining y data points
    """

    m = len(arrX)

    arrX = np.copy(arrX)
    a = np.copy(arrY)
    for k in range(1, m):
        a[k:m] = (a[k:m] - a[k - 1]) / (arrX[k:m] - arrX[k - 1])

    return a


def newton_interpolation(x_data, y_data, x):
    """
    x_data: data points at x
    y_data: data points at y
    x: evaluation point(s)
    """
    a = newtonInterp_coefficient(x_data, y_data)
    n = len(x_data) - 1  # Degree of polynomial
    p = a[n]

    for k in range(1, n + 1):
        p = a[n - k] + (x - x_data[n - k]) * p

    return p

'''
def lagrange_interp(desired_x, x_axis, y_axis):
    n = len(x_axis)
    result = 0
    for i in range(n):
        L = y_axis[i]
        for j in range(n):
            if i != j:
                L *= (desired_x - x_axis[j]) / (x_axis[i] - x_axis[j])
        result += L
    return result





result1_y1 = lagrange_interp(x_interp, x, y1)
result1_y2 = lagrange_interp(x_interp, x, y2)
print("The interpolated result at x = ", x_interp, " is ", result1_y1, "and ", result1_y2)
order = 5
x = np.array([])
y1 = np.array([])
y2 = np.array([])
left = minimal_pos - 1
right = minimal_pos
for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        y2 = np.append(y2, temp_y2[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        y2 = np.append(y2, temp_y2[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            y2 = np.append(y2, temp_y2[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            y2 = np.append(y2, temp_y2[right])
            right = right + 1
'''

if __name__ == '__main__':
    '''result2_y1 = lagrange_interp(x_interp, x, y1)
    result2_y2 = lagrange_interp(x_interp, x, y2)
    print("The interpolated result at x = ", x_interp, " is ", result2_y1, "and ", result2_y2)
    print("The relative approximate error is: ", error(result2_y1, result1_y1), "and", error(result2_y2, result1_y2))
    plt.plot(temp_x, temp_y1, label="Pressure 1 bar")
    plt.plot(temp_x, temp_y2, label="Pressure 2 bar")
    plt.plot(x, y1, "o")
    plt.plot(x, y2, "o")
    plt.plot(x_interp, result2_y1, "s")
    plt.plot(x_interp, result2_y2, "s")
    plt.legend()
    plt.grid(True)
    plt.show()'''
