import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    graph_x = np.linspace(2, 12, 60)

    coefficient = np.copy(coeff)
    y2 = coefficient[0] * np.exp(coefficient[1] * graph_x)
    plt.plot(graph_x, y2, label="Exponential Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def exponential_regression(a, b):
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

    A = np.exp(a0)
    return (A, a1)


if __name__ == '__main__':
    x_data = np.array([4.0, 5.0, 7.0, 8.0, 9.0, 10.0])
    y_data = np.array([5800.0, 5700.0, 4200.0, 4100.0, 3100.0, 2500.0])

    # x_data = np.array([0, 5, 10, 15, 20, 25, 30])
    # y_data = np.array([1000, 550, 316, 180, 85, 56, 31])

    log_y = np.log(y_data)

    a = exponential_regression(x_data, log_y)

    print("a = %f" % a[0])
    print("b = %f" % a[1])

    ans = a[0] * np.exp(a[1] * 40)
    print("ans = %f" % ans)

    graph(x_data, y_data, a)
