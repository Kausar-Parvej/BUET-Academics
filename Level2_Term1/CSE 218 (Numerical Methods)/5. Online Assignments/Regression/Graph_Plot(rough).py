import numpy as np
import matplotlib.pyplot as plt


def graph(x_values, y_values):
    plt.close('all')
    plt.plot(x_values, y_values, "o", label="Point Plot")

    plt.grid()
    plt.show()


if __name__ == '__main__':
    x_data = np.array([])
    y_data = np.array([])

    input_data = np.genfromtxt("input2.csv", delimiter=",", skip_header=1)
    # input_data = np.genfromtxt("input.txt", dtype=float, skip_header=1)
    for row in input_data:
        x_data = np.append(x_data, float(row[0]))
        y_data = np.append(y_data, float(row[1]))

    x_data = np.array([4.0, 5.0, 7.0, 8.0, 9.0, 10.0])
    y_data = np.array([5800.0, 5700.0, 4200.0, 4100.0, 3100.0, 2500.0])

    graph(x_data, y_data)
