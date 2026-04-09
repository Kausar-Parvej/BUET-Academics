import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("datapoints.txt", delimiter="	", skip_header=1)
# print(data)
all_x = np.array([])
all_y = np.array([])

for row in data:
    all_x = np.append(all_x, float(row[0]))
    all_y = np.append(all_y, float(row[1]))

n = len(all_x)
# print(temp_x,temp_y1,temp_y2)
x_value = float(input("Value of X:"))

min_pos = n
for i in range(n):

    if x_value == all_x[i]:
        print("Value don't need to be interpolated ,it's already given :", all_y[i])
        exit()
    if x_value < all_x[i]:
        min_pos = i
        break


def error(p, q):
    return abs((p - q) / p) * 100



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
left = min_pos - 1
right = min_pos

for i in range(order):
    if left < 0:
        x = np.append(x, all_x[right])
        y1 = np.append(y1, all_y[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, all_x[left])
        y1 = np.append(y1, all_y[left])
        left = left - 1
    else:
        dif_l = abs(x_value - all_x[left])
        dif_r = abs(x_value - all_x[right])
        if dif_l < dif_r:
            x = np.append(x, all_x[left])
            y1 = np.append(y1, all_y[left])
            left = left - 1
        else:
            x = np.append(x, all_x[right])
            y1 = np.append(y1, all_y[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_value)
o2 = result1_y1
print("The interpolated result at x = ", x_value, " is ", result1_y1)

print("\n")
print("Order = 3:")
order = 3 + 1
x = np.array([])
y1 = np.array([])
left = min_pos - 1
right = min_pos

for i in range(order):
    if left < 0:
        x = np.append(x, all_x[right])
        y1 = np.append(y1, all_y[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, all_x[left])
        y1 = np.append(y1, all_y[left])
        left = left - 1
    else:
        dif_l = abs(x_value - all_x[left])
        dif_r = abs(x_value - all_x[right])
        if dif_l < dif_r:
            x = np.append(x, all_x[left])
            y1 = np.append(y1, all_y[left])
            left = left - 1
        else:
            x = np.append(x, all_x[right])
            y1 = np.append(y1, all_y[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_value)
o3 = result1_y1
print("The interpolated result at x = ", x_value, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o2))

print("\n")
print("Order = 4:")
order = 4 + 1
x = np.array([])
y1 = np.array([])
left = min_pos - 1
right = min_pos

for i in range(order):
    if left < 0:
        x = np.append(x, all_x[right])
        y1 = np.append(y1, all_y[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, all_x[left])
        y1 = np.append(y1, all_y[left])
        left = left - 1
    else:
        dif_l = abs(x_value - all_x[left])
        dif_r = abs(x_value - all_x[right])
        if dif_l < dif_r:
            x = np.append(x, all_x[left])
            y1 = np.append(y1, all_y[left])
            left = left - 1
        else:
            x = np.append(x, all_x[right])
            y1 = np.append(y1, all_y[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_value)
o4 = result1_y1
print("The interpolated result at x = ", x_value, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o3))

print("\n")
print("Order = 5:")
order = 5 + 1
x = np.array([])
y1 = np.array([])
left = min_pos - 1
right = min_pos

for i in range(order):
    if left < 0:
        x = np.append(x, all_x[right])
        y1 = np.append(y1, all_y[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, all_x[left])
        y1 = np.append(y1, all_y[left])
        left = left - 1
    else:
        dif_l = abs(x_value - all_x[left])
        dif_r = abs(x_value - all_x[right])
        if dif_l < dif_r:
            x = np.append(x, all_x[left])
            y1 = np.append(y1, all_y[left])
            left = left - 1
        else:
            x = np.append(x, all_x[right])
            y1 = np.append(y1, all_y[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_value)
o5 = result1_y1
print("The interpolated result at x = ", x_value, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o4))

print("\n")
print("Order = 6:")
order = 6 + 1
x = np.array([])
y1 = np.array([])
left = min_pos - 1
right = min_pos

for i in range(order):
    if left < 0:
        x = np.append(x, all_x[right])
        y1 = np.append(y1, all_y[right])
        right = right + 1
    elif right >= n:
        x = np.append(x, all_x[left])
        y1 = np.append(y1, all_y[left])
        left = left - 1
    else:
        dif_l = abs(x_value - all_x[left])
        dif_r = abs(x_value - all_x[right])
        if dif_l < dif_r:
            x = np.append(x, all_x[left])
            y1 = np.append(y1, all_y[left])
            left = left - 1
        else:
            x = np.append(x, all_x[right])
            y1 = np.append(y1, all_y[right])
            right = right + 1

result1_y1 = newton_interpolation(x, y1, x_value)
o6 = result1_y1
print("The interpolated result at x = ", x_value, " is ", result1_y1)
print("The absolute approximate relative error: ", error(result1_y1, o5))

plt.plot(all_x, all_y, label="graph")
plt.plot(x, y1, "o")
plt.plot(x_value, result1_y1, "s")
plt.legend()
plt.grid(True)
plt.show()
