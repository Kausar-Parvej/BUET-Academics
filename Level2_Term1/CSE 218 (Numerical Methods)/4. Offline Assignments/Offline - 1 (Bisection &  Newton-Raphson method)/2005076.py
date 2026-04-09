import numpy as np
import matplotlib.pyplot as plt

R = 6 / 100


def f(x):
    return (x * x * x / 3) - (R * x * x) + (4 * R * R * R * 0.55 / 3)


def derivative_f(x):
    return (x * x) - (2 * R * x)


def graph():
    plt.close('all')
    x = np.linspace(-0.1, 0.2, 1000)
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


def newton_raphson(initial_guess, expected_error, max_iteration):
    print('\n\n   ----> NEWTON-RAPHSON METHOD IMPLEMENTATION <----')
    iteration = 1
    flag = True
    old_root = initial_guess
    root = 0.0

    while flag:
        if derivative_f(initial_guess) == 0.0:
            print("\n     ERROR! divide by zero")
            break

        root = initial_guess - (f(initial_guess) / derivative_f(initial_guess))
        error = abs(((root - old_root) / root) * 100)
        print('Iteration -> %d,  \troot = %0.6f   \trelative error = %0.6f' % (iteration, root, error), '%')

        flag = error > expected_error
        old_root = root
        initial_guess = root
        iteration = iteration + 1

        if iteration > max_iteration:
            print("\n     ERROR! not convergent")
            break

    return root


if __name__ == '__main__':
    graph()

    bisection_root = bisection(0.05, 0.07, 0.5, 100)
    print('\n    Root from Bisection method is : %0.4f m' % bisection_root)

    NR_root = newton_raphson(0.1, 0.5, 100)
    print('\n    Root from Newton-Raphson method is : %0.4f m' % NR_root)
