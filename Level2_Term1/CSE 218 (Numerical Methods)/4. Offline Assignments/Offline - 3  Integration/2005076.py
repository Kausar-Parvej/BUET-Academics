import math
import sys

import numpy as np
import matplotlib.pyplot as plt

C_methanol = 0.0005
X_initial = 0.000122


def f(x):
    if x == 0:
        print("Divided By Zero Error!")
        sys.exit()

    return -(6.73 * x + 0.00000006725 + 0.000726 * C_methanol) / (0.00000000000362 * x + 0.00000003908 * x * C_methanol)
    # return x/(1 + x**2)


def relative_error(exact_value, calculated_value):
    return abs((exact_value - calculated_value) / exact_value) * 100


def trapezoid_rule(lower_limit, upper_limit, segment_number):
    height = (upper_limit - lower_limit) / segment_number
    integration_result = f(lower_limit) + f(upper_limit)

    for i in range(1, segment_number):
        segment = lower_limit + i * height
        integration_result += 2 * f(segment)

    integration_result = integration_result * height / 2

    return integration_result


def simpsons_13_rule(lower_limit, upper_limit, segment_number):
    if segment_number % 2 != 0:
        segment_number += 1

    height = (upper_limit - lower_limit) / segment_number
    integration_result = f(lower_limit) + f(upper_limit)

    for i in range(1, segment_number):
        segment = lower_limit + i * height
        if i % 2 == 0:
            integration_result += 2 * f(segment)
        else:
            integration_result += 4 * f(segment)

    integration_result = integration_result * height / 3

    return integration_result


def graph():
    plt.close('all')
    # x = np.linspace(-5, 5, 1000)
    x = [0.000122, 0.000120, 0.00010, 0.00008, 0.00006, 0.00004, 0.00002]
    y = [0]
    for index in range(1, 7):
        integrated_time = simpsons_13_rule(0.000122, x[index], 10)
        y = np.append(y, integrated_time)

    plt.plot(x, y, color='green', label='time vs. oxygen_concentration')
    plt.legend(loc='best')
    plt.xlabel("Oxygen Concentration (moles/cm^3)")
    plt.ylabel("Time (second)")

    plt.plot(x, y, "o", color='red')
    plt.grid()
    plt.show()


if __name__ == '__main__':
    segment_num = int(input("Enter number of Segment: "))

    print('\n -->Implementation of Multiple_Segment Trapezoid Rule<--')
    integration1 = trapezoid_rule(0.75 * X_initial, 0.25 * X_initial, 1)
    print('       Number of Segment = 1 : Integration result -> %0.4f sec' % integration1)
    for i in range(2, segment_num + 1):
        integration2 = trapezoid_rule(0.75 * X_initial, 0.25 * X_initial, i)
        error = relative_error(integration2, integration1)
        print(
            '       Number of Segment = %d : Integration Result -> %0.4f sec, Approximate Relative Error -> ' % (
                i, integration2), error, '%')
        integration1 = integration2

    print('\n\n -->Implementation of Simpson’s 1/3 Rule<--')
    integration1 = simpsons_13_rule(0.75 * X_initial, 0.25 * X_initial, 2)
    print('       Number of Segment = 2 : Integration result -> %0.4f sec' % integration1)
    for i in range(2, segment_num + 1):
        integration2 = simpsons_13_rule(0.75 * X_initial, 0.25 * X_initial, 2 * i)
        error = relative_error(integration2, integration1)
        print(
            '       Number of Segment = %d : Integration Result -> %0.4f sec, Approximate Relative Error -> ' % (
                2 * i, integration2), error, '%')
        integration1 = integration2

    graph()
