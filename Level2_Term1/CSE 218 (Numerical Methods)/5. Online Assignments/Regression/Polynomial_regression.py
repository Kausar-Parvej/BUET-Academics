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

    graph_x = np.linspace(2, 12, 50)

    coefficient = np.copy(coeff)
    y2 = 0
    # y2 = coefficient[0] + coefficient[1] * graph_x + coefficient[2] * graph_x ** 2
    for index in range(n):
        y2 += coefficient[index] * graph_x ** index
    plt.plot(graph_x, y2, label="Polynomial Regression")
    plt.xlabel("x axis")
    plt.ylabel("y axis")

    plt.legend(loc="best")
    plt.grid()
    plt.show()


def polynomial_regression(a, b):
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

    # x_data = np.array([0.0, 0.183, 0.36, 0.5324, 0.702, 0.867, 1.0244, 1.1774, 1.329, 1.479, 1.5, 1.56])
    # y_data = np.array([0.0, 306.0, 612.0, 917.0, 1223.0, 1529.0, 1835.0, 2140.0, 2446.0, 2752.0, 2767.0, 2896.0])

    x_data = np.array([4.0, 5.0, 7.0, 8.0, 9.0, 10.0])
    y_data = np.array([5800.0, 5700.0, 4200.0, 4100.0, 3100.0, 2500.0])

    co_efficients = polynomial_regression(x_data, y_data)
    print("\nThe Co-efficients are : ")
    for i in range(n):
        print("a%d = " % i, end=" ")
        print(co_efficients[i])

    graph(x_data, y_data, co_efficients)
