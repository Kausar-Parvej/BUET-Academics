import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    graph_x = np.linspace(0.2, 5, 50)

    coefficient = np.copy(coeff)
    y2 = (coefficient[0] * graph_x ** 2) / (coefficient[1] + graph_x ** 2)
    # y2 = 0.2 * graph_x / (3 + graph_x)
    plt.plot(graph_x, y2, label="Growth-Model Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.plot(2.0, ans1, "s")
    plt.plot(4.5, ans2, "s")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def growthModel_regression(a, b):  # y = ax^2 / (b+x^2)
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

    A = 1 / a0
    B = A * a1
    return (A, B)


if __name__ == '__main__':
    x_data = np.array([0.5, 0.8, 1.5, 2.5, 4.0])
    y_data = np.array([1.1, 2.4, 5.3, 7.6, 8.9])

    modified_x = (1 / x_data ** 2)
    modified_y = (1 / y_data)

    co_eff = growthModel_regression(modified_x, modified_y)

    print("a = %f" % co_eff[0])
    print("b = %f" % co_eff[1])

    ans1 = (co_eff[0] * 2.0 ** 2) / (co_eff[1] + 2.0 ** 2)
    ans2 = (co_eff[0] * 4.5 ** 2) / (co_eff[1] + 4.5 ** 2)

    print("\nAt x=2.0, y= %f" % ans1)
    print("At x=4.5, y= %f" % ans2)

    graph(x_data, y_data, co_eff)
