import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("datapoints.txt", delimiter="	", skip_header=1)
# print(data)
temp_x = np.array([])
temp_y1 = np.array([])

for row in data:
    temp_x = np.append(temp_x, float(row[0]))
    temp_y1 = np.append(temp_y1, float(row[1]))

n = len(temp_x)
# print(temp_x,temp_y1,temp_y2)
x_interp = float(input("Value of X:"))

minimal_pos = n
for i in range(n):

    if x_interp == temp_x[i]:
        print("Value don't need to be interpolated ,it's already given :", temp_y1[i])
        exit()
    if x_interp < temp_x[i]:
        minimal_pos = i
        break


def error(p, q):
    return abs((p - q) / p) * 100


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


def newtonInterp_coefficient(arrX, arrY):
    m = len(arrX)

    arrX = np.copy(arrX)
    a = np.copy(arrY)
    for k in range(1, m):
        a[k:m] = (a[k:m] - a[k - 1]) / (arrX[k:m] - arrX[k - 1])

    return a


def newton_interpolation(x_data, y_data, x):
    a = newtonInterp_coefficient(x_data, y_data)
    print("Co-efficient:")
    print(a)
    n = len(x_data) - 1
    p = a[n]

    for k in range(1, n + 1):
        p = a[n - k] + (x - x_data[n - k]) * p

    return p


print("\n")
print("Order = 2:")
order = 2 + 1
x = np.array([])
y1 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_interp)
o2 = result1_y1
print("The interpolated result at x = ", x_interp, " is ", result1_y1)

print("\n")
print("Order = 3:")
order = 3 + 1
x = np.array([])
y1 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_interp)
o3 = result1_y1
print("The interpolated result at x = ", x_interp, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o2))

print("\n")
print("Order = 4:")
order = 4 + 1
x = np.array([])
y1 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_interp)
o4 = result1_y1
print("The interpolated result at x = ", x_interp, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o3))

print("\n")
print("Order = 5:")
order = 5 + 1
x = np.array([])
y1 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_interp)
o5 = result1_y1
print("The interpolated result at x = ", x_interp, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o4))

print("\n")
print("Order = 6:")
order = 6 + 1
x = np.array([])
y1 = np.array([])
left = minimal_pos - 1
right = minimal_pos

for i in range(order):
    if left < 0:
        x = np.append(x, temp_x[right])
        y1 = np.append(y1, temp_y1[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, temp_x[left])
        y1 = np.append(y1, temp_y1[left])
        left = left - 1
    else:
        dif_l = abs(x_interp - temp_x[left])
        dif_r = abs(x_interp - temp_x[right])
        if dif_l < dif_r:
            x = np.append(x, temp_x[left])
            y1 = np.append(y1, temp_y1[left])
            left = left - 1
        else:
            x = np.append(x, temp_x[right])
            y1 = np.append(y1, temp_y1[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_interp)
o6 = result1_y1
print("The interpolated result at x = ", x_interp, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o5))

plt.plot(temp_x, temp_y1, label="graph")
plt.plot(x, y1, "o")
plt.plot(x_interp, result1_y1, "s")
plt.legend()
plt.grid(True)
plt.show()
