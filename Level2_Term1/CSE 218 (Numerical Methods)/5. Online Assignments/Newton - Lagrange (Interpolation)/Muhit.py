import numpy
import matplotlib.pyplot as plt

numv = int(input())
A = numpy.zeros((2, numv))

for i in range(2):
    # for j in range(numv):
    A[i] = list(input().split())

nit = int(input())

nit = nit + 1

for i in range(numv):
    for j in range(i + 1, numv):
        if A[0][i] > A[0][j]:
            A[:, [i, j]] = A[:, [j, i]]

x = float(input())
ind = 0
fl = 0
if x > A[0][numv - 1] or x < A[0][0]:
    print("Out of Range")

else:
    while ind < numv and A[0][ind] < x:
        ind = ind + 1

    if A[0][ind] == x:
        fl = 1

    if fl == 1:
        print(A[1][ind])
        # plt.plot(A[0], A[1])
        # plt.show()

    else:

        right = ind
        left = right - 1
        it = 2

        while left > 0 and right < numv - 1 and it < nit:
            if numpy.fabs(A[0][left - 1] - x) < numpy.fabs(A[0][right + 1] - x):
                left = left - 1

            else:
                right = right + 1

            it = it + 1

        if left == 0:
            while right < numv - 1 and it < nit:
                right = right + 1
                it = it + 1

        elif right == numv - 1:
            while left > 0 and it < nit:
                left = left - 1
                it = it + 1
        # lagrange

        ans = 0
        coefficientArray = numpy.ones(right - left + 1)

        for i in range(right - left + 1):
            coeff = 1
            for j in range(right - left + 1):

                if i != j:
                    coeff = coeff * (x - A[0][left + j]) / (A[0][left + i] - A[0][left + j])
                    coefficientArray[i] = coefficientArray[i] / (A[0][left + i] - A[0][left + j])

            ans = ans + coeff * A[1][left + i]
            coefficientArray[i] = coefficientArray[i] * A[1][left + i]

        for i in range(right - left + 1):
            print(coefficientArray[i])

        print(ans)


        def f(x):
            return (x - A[0][left + 1]) * (x - A[0][left + 2]) * (x - A[0][left + 3]) * coefficientArray[0] + \
                (x - A[0][left + 0]) * (x - A[0][left + 2]) * (x - A[0][left + 3]) * coefficientArray[1] + \
                (x - A[0][left + 0]) * (x - A[0][left + 1]) * (x - A[0][left + 3]) * coefficientArray[2] + \
                (x - A[0][left + 0]) * (x - A[0][left + 1]) * (x - A[0][left + 2]) * coefficientArray[3]


        xi = numpy.linspace(-100, 100, 1000)
        plt.plot(xi, f(xi))
        plt.plot(x, ans)
        plt.show()

        # lagrange end

        # newton divided difference

        newtonTable = numpy.zeros((right - left + 1, right - left + 1))

        for i in range(right - left + 1):
            newtonTable[i][0] = A[1][left + i]

        for j in range(1, right - left + 1):
            for i in range(right - left + 1 - j):
                newtonTable[i][j] = (newtonTable[i + 1][j - 1] - newtonTable[i][j - 1]) / (
                        A[0][left + i + j] - A[0][left + i])


        def func(xv):
            ans = newtonTable[0][right - left]
            for i in range(right - left - 1, -1, -1):
                ans = ans * (xv - A[0][left + i]) + newtonTable[0][i]
            print(ans)


        def g(x):
            return newtonTable[0][0] + newtonTable[0][1] * (x - A[0][left + 0]) + \
                newtonTable[0][2] * (x - A[0][left + 0]) * (x - A[0][left + 1]) + \
                newtonTable[0][3] * (x - A[0][left + 0]) * (x - A[0][left + 1]) * (x - A[0][left + 2])


        print(func(x))
        '''def g(x):
            return newtonTable[0][0]+newtonTable[0][1]*(x-A[0][left+0])+\
                newtonTable[0][2]*(x-A[0][left+0])*(x-A[0][left+1])+\
                newtonTable[0][3]*(x-A[0][left+0])*(x-A[0][left+1])*(x-A[0][left+2])
    
    
        
        xi = numpy.linspace(-5, 2, 1000)
        plt.plot(xi, g(xi))
        plt.plot(x, ans)
        plt.grid()
        plt.show()'''

        # newton div end
