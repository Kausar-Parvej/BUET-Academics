import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    graph_x = np.linspace(0.001, 5.0, 50)

    coefficient = np.copy(coeff)
    y2 = coefficient[0] * (graph_x ** coefficient[1])
    plt.plot(graph_x, y2, label="Power-Model Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def powerModel_regression(a, b):  # y = ax^b
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
    x_data = np.array([4.0, 2.25, 1.45, 1.0, 0.65, 0.25, 0.006])
    y_data = np.array([0.398, 0.298, 0.238, 0.198, 0.158, 0.098, 0.048])

    # x_data = np.array([0, 5, 10, 15, 20, 25, 30])
    # y_data = np.array([1000, 550, 316, 180, 85, 56, 31])

    log_x = np.log(x_data)
    log_y = np.log(y_data)

    co_eff = powerModel_regression(log_x, log_y)

    print("a = %f" % co_eff[0])
    print("b = %f" % co_eff[1])

    # ans = a[0] * np.exp(a[1] * 40)
    # print("ans = %f" % ans)

    graph(x_data, y_data, co_eff)
