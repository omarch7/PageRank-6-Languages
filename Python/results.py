import numpy as np
import math
import matplotlib.pyplot as plt


def main():
    array = []
    with open('results/PR_2015280261.txt', 'r') as f:
        for line in f:
            array.append(float(line[:-1].split('\t')[1]))
    data = np.sort(np.array(array), axis=-1)

    plt.plot(np.log(data[::-1]), color='g', linewidth=2.0)
    plt.title("Distribution of PageRank Scores")
    plt.ylabel("PageRank")
    plt.xlabel("Position")
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    main()
