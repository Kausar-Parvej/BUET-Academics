import numpy as np
import matplotlib.pyplot as plt

W = 1.75
E = 50000.0
L = 450.0
I = 30000.0


def f(x):
    return (W / (120 * E * I * L)) * ((-5 * x ** 4) + (6 * L * L * x * x) + (L ** 4))


def graph():
    plt.close('all')
    x = np.linspace(-600, 600, 1000)
    # x = np.linspace(-5, 5, 1000)
    y = f(x)
    plt.plot(x, y, label='graph_1')
    plt.legend(loc='best')

    plt.xlabel("X")
    plt.ylabel("F(X)")
    plt.grid()
    plt.show()


def bisection(lower_bound, higher_bound, expected_error, max_iteration):
    print('\n\n    ----> BISECTION METHOD IMPLEMENTATION <-------')
    flag = True
    old_root = higher_bound
    root = 0.0
    iteration = 1

    while flag:
        root = (lower_bound + higher_bound) / 2
        if f(lower_bound) * f(root) < 0:
            higher_bound = root
        elif f(lower_bound) * f(root) == 0:
            return root
        else:
            lower_bound = root

        error = abs(((root - old_root) / root) * 100)
        print('Iteration -> %d,  \troot = %0.6f   \trelative error = %0.6f' % (iteration, root, error), '%')
        old_root = root
        flag = error > expected_error
        if iteration > max_iteration:
            flag = False
        iteration = iteration + 1

    return root


if __name__ == '__main__':
    graph()

    bisection_root = bisection(500, 550, 0.5, 100)
    print('\n    Root from Bisection method is : %0.4f cm' % bisection_root)
