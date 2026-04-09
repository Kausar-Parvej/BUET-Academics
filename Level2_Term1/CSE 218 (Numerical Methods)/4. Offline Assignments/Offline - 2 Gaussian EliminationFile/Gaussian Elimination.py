# x^2 + y^2 + ax + by + c = 0
# ax + by + c = - (x^2 + y^2)

import sys

import numpy as np


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


if __name__ == '__main__':
    n = int(input())
    co_matrix = np.zeros((n, n))
    constant_matrix = np.zeros((n, 1))

    np.set_printoptions(suppress=True, precision=4)

    '''for i in range(n):
        for j in range(n):
            co_matrix[i][j] = float(input())'''

    for i in range(n):
        input_row = input().split()
        for j in range(n):
            co_matrix[i][j] = float(input_row[j])

    for k in range(n):
        constant_matrix[k][0] = float(input())

    print()
    result = gaussianElimination(co_matrix, constant_matrix, True, True)

    print('\n\tresult:')
    for a in range(n):
        print('\t\t%0.4f' % result[a])
