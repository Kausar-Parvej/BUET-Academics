import sys

import numpy as np
import matplotlib.pyplot as plt


def gaussianElimination(A, B, pivot, showall):
    solution_matrix = np.zeros(n)
    step = 1
    for u in range(n):
        if pivot:
            max_index = u
            max_co = A[max_index][u]

            for ko in range(u + 1, n):
                if abs(A[ko][u]) > max_co:
                    max_index = ko
                    max_co = A[ko][u]

            if max_index != u:
                for ki in range(n):
                    temp = A[u][ki]
                    A[u][ki] = A[max_index][ki]
                    A[max_index][ki] = temp

                temp2 = B[u][0]
                B[u][0] = B[max_index][0]
                B[max_index][0] = temp2

        for v in range(u + 1, n):
            factor = A[v][u] / A[u][u]

            for w in range(u + 1, n):
                A[v][w] -= A[u][w] * factor
            B[v][0] -= B[u][0] * factor
            A[v][u] = 0

        if showall:
            print("Sub-Step %d:" % step)
            print(A)
            print()
            print(B)
            print()
            step += 1

    determinant = 1
    for it in range(n):
        determinant *= A[it][it]
    if showall:
        print('Determinant of the coefficient matrix is : %0.4f ' % determinant)
    if determinant == 0:
        sys.exit('ERROR! Infinite Solutions')

    for p in range(n - 1, -1, -1):
        solution_matrix[p] = B[p][0]

        for m in range(p + 1, n):
            solution_matrix[p] -= A[p][m] * solution_matrix[m]
        solution_matrix[p] = solution_matrix[p] / A[p][p]

    return solution_matrix


def graph(x_values, y_values, coeff):
    plt.close('all')
    plt.plot(x_values, y_values, "o")

    graph_x = np.linspace(0.7, 7.0, 50)

    coefficient = np.copy(coeff)
    # y2 = coefficient[0] + coefficient[1] * graph_x + coefficient[2] * graph_x ** 2

    y2 = coefficient[1] + coefficient[2] * graph_x + coefficient[0] / graph_x

    plt.plot(graph_x, y2, label="Polynomial Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.plot(2.5, ans1, "s",label="y(2.5)")
    plt.plot(5.5, ans2, "s", label="y(5.5)")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def polynomial_regression(a, b):  # y = c + ax + bx^2
    x = np.copy(a)
    y = np.copy(b)
    data_size = np.size(a)

    co_matrix = np.zeros((n, n))
    constant_matrix = np.zeros((n, 1))

    for i in range(n):
        for j in range(n):
            co_matrix[i][j] = (np.sum(x ** (i + j)))
    # print(co_matrix)

    for k in range(n):
        constant_matrix[k][0] = np.sum(y * (x ** k))
    # print(constant_matrix)

    result_matrix = gaussianElimination(co_matrix, constant_matrix, True, False)
    return result_matrix


if __name__ == '__main__':
    '''for quadratic equation -> n=3'''
    n = 3

    x_data = np.array([1.0, 2.0, 3.0, 4.0, 5.0])
    y_data = np.array([2.2, 2.8, 3.6, 4.5, 5.5])

    modified_y = y_data * x_data

    co_efficients = polynomial_regression(x_data, modified_y)  # yx = c + ax + bx^2
    print("\nThe Co-efficients are :  (y = a + bx + c/x)")
    print("a = %f" % co_efficients[1])
    print("b = %f" % co_efficients[2])
    print("c = %f" % co_efficients[0])

    ans1 = co_efficients[1] + co_efficients[2] * 2.5 + co_efficients[0] / 2.5
    ans2 = co_efficients[1] + co_efficients[2] * 5.5 + co_efficients[0] / 5.5

    print("\nAt x=2.5, y= %f" % ans1)
    print("At x=5.5, y= %f" % ans2)

    graph(x_data, y_data, co_efficients)
