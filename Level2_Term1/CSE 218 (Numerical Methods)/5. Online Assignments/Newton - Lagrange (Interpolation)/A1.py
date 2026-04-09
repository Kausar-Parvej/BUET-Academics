import numpy
import matplotlib.pyplot as mpt


def determineCoff(alx, alfx):
    order = len(alx)

    coffMat = numpy.zeros((order, order))
    coffMat[:, 0] = alfx

    for a in range(1, order):
        for b in range(order - a):
            if alx[b + a] - alx[b] == 0:
                print(f"f(x) = {alfx[b]} or Error calculation.")
                exit(0)
            coffMat[b, a] = (coffMat[b + 1, a - 1] - coffMat[b, a - 1]) / (alx[b + a] - alx[b])

    print(coffMat)
    return coffMat


def product(alx, n, x):
    p = 1
    for i in range(n):
        p *= (x - alx[i])
    return p


def get_fxNewton(x, alx, alfx):
    order = len(alx)

    coff = determineCoff(alx, alfx)[0, :]
    fx = coff[0]
    for i in range(1, len(alx)):
        fx += coff[i] * product(alx, i, x)

    return fx


def get_fxLagrange(x, alx, alfx):
    fx = 0
    for i in range(len(alx)):
        l = 1
        for j in range(len(alx)):
            if i != j:
                if alx[i] == alx[j]:
                    print(f"f(x) = {alx[i]} or Error calculation.")
                    exit(0)
                l *= (x - alx[j]) / (alx[i] - alx[j])
        fx += l * alfx[i]

    return fx


def plot(x, y, unkown):
    print(f"Newton = {get_fxNewton(unkown, x, y)}")
    print(f'Lagrange = {get_fxLagrange(unkown, x, y)}')
    # x_n = numpy.arange(-5, 2.1, .1)
    x_n = numpy.linspace(-5, 35, 4000)
    # y_n = get_fxNewton(x_n, x ,y)
    y_n = get_fxLagrange(x_n, x, y)
    mpt.figure(figsize=(10, 5))
    mpt.plot(x, y, 'bo')
    mpt.plot(x_n, y_n, '-r')
    mpt.grid()
    mpt.show()


def closest(points, new):
    closest_point = None
    closest_distance = None
    for point in points:
        distance = abs(point[0] - new)
        if closest_distance is None or distance < closest_distance:
            closest_point = point
            closest_distance = distance
    return closest_point


def main():
    T = []
    with open("input.txt", "r") as file1:
        for line in file1.readlines():
            f_list = [float(i) for i in line.split(" ")]
            t = [float(f_list[0]), float(f_list[1])]
            T.append(t)
    inter = float(input("Enter x = "))
    newT = []
    for i in range(4):
        p = closest(T, inter)
        newT.append(p)
        T.remove(p)

    arr = numpy.array(newT)
    alx = arr[:, 0]
    alfx = arr[:, 1]
    plot(alx, alfx, inter)

    # print(arr)
    #
    # inter = float(input("Enter x = "))
    #
    # arr = arr[:,0]-inter
    # print(arr)


main()
