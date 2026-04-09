import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    coefficient = np.copy(coeff)
    graph_x = np.linspace(0, 1.6, 50)
    y2 = coefficient[0] + coefficient[1] * graph_x
    plt.plot(graph_x, y2, label="Linear Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def linear_regression(a, b):
    x = np.copy(a)
    y = np.copy(b)
    n = np.size(a)

    mean_X = np.mean(x)
    mean_Y = np.mean(y)

    sum_X = np.sum(x)
    sum_Y = np.sum(y)
    sum_XY = np.sum(x * y)
    sum_XX = np.sum(x * x)

    a1 = (n * sum_XY - sum_X * sum_Y) / (n * sum_XX - sum_X * sum_X)
    a0 = mean_Y - a1 * mean_X

    return (a0, a1)


if __name__ == '__main__':
    x = np.array([])
    y = np.array([])

    # input_data = np.genfromtxt("input2.csv", delimiter=",", skip_header=1)
    input_data = np.genfromtxt("input.txt", dtype=float, skip_header=1)
    for row in input_data:
        x_data = np.append(x, float(row[0]))
        y_data = np.append(y, float(row[1]))

    x_data = np.array([0.0, 0.183, 0.36, 0.5324, 0.702, 0.867, 1.0244, 1.1774, 1.329, 1.479, 1.5, 1.56])
    y_data = np.array([0.0, 306.0, 612.0, 917.0, 1223.0, 1529.0, 1835.0, 2140.0, 2446.0, 2752.0, 2767.0, 2896.0])

    co_eff = linear_regression(x_data, y_data)

    print("a0 = %f" % co_eff[0])
    print("a1 = %f" % co_eff[1])

    graph(x_data, y_data, co_eff)
