import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    graph_x = np.linspace(4, 10, 50)

    coefficient = np.copy(coeff)
    y2 = (coefficient[0] * graph_x) / (coefficient[1] + graph_x)
    # y2 = 0.2 * graph_x / (3 + graph_x)
    plt.plot(graph_x, y2, label="Growth-Model Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def growthModel_regression(a, b):  # y = ax / (b+x)
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
    '''x_data = np.array([0.2, 0.3, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.8, 2.4, 2.8, 4.0, 6.0, 8.0, 10.0, 12.0])
    y_data = np.array(
        [0.0125, 0.01818, 0.023529, 0.0333, 0.0421, 0.0571, 0.06, 0.06365, 0.07502, 0.088889, 0.096525, 0.11428,
         0.13333, 0.145348, 0.153846, 0.16])'''

    # x_data = np.array([0, 5, 10, 15, 20, 25, 30])
    # y_data = np.array([1000, 550, 316, 180, 85, 56, 31])

    x_data = np.array([4.0, 5.0, 7.0, 8.0, 9.0, 10.0])
    y_data = np.array([5800.0, 5700.0, 4200.0, 4100.0, 3100.0, 2500.0])

    modified_x = (1 / x_data)
    modified_y = (1 / y_data)

    co_eff = growthModel_regression(modified_x, modified_y)

    print("a = %f" % co_eff[0])
    print("b = %f" % co_eff[1])

    graph(x_data, y_data, co_eff)
