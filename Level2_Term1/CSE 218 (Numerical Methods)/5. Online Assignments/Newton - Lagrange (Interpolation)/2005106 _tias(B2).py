import numpy as np
import matplotlib.pyplot as plt

day = []
stock = []
space = []


def readFromTxt(Filename):
    infile = open(Filename, "r")
    title = infile.readline()
    for number in infile:
        numbers = number.split()
        day.append(float(numbers[0]))
        stock.append(float(numbers[1]))


def lagrange_interp(x, y, xi):
    """
    Perform Lagrange interpolation at xi using data points (x, y)
    """
    n = len(x)
    yi = 0
    for i in range(n):
        # Compute the Lagrange polynomial Li(x)
        Li = 1
        for j in range(n):
            if j != i:
                Li *= (xi - x[j]) / (x[i] - x[j])
        yi += y[i] * Li
    return yi


# task 1
readFromTxt("stock.txt")
daysArray = np.array(day)
stocksArray = np.array(stock)
# task 2
n = len(day)
inputDay = float(input("Input a day:"))
xlist = []
ylist = []
for i in range(n - 1):
    if inputDay > day[i] and inputDay < day[i + 1] and i > 1 and i < n - 2:
        xlist.append(day[i - 2])
        xlist.append(day[i - 1])
        xlist.append(day[i])
        xlist.append(day[i + 1])
        xlist.append(day[i + 2])
        ylist.append(stock[i - 2])
        ylist.append(stock[i - 1])
        ylist.append(stock[i])
        ylist.append(stock[i + 1])
        ylist.append(stock[i + 2])
        break

result = lagrange_interp(xlist, ylist, inputDay)
print(result)
# task 3

# task 4
plt.plot(day, stock)
plt.scatter(day, stock)
plt.axhline(color='black')
plt.axvline(color='black')
plt.grid()
plt.show()
