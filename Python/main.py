from PR.BasicGraph import BasicGraph
import time


def main():
    graph = BasicGraph()
    start = time.time()
    with open('/Users/omar/Documents/Tsinghua/Spring 2016/CPP/PageRank/linkgraph.txt', 'r') as f:
        for line in f:
            values = line[:-1].split("\t")
            graph.add_edge(values[0], values[1])
    end = time.time() - start
    print("Loaded into memory in " + str(end * 1000)) + "ms"
    graph.calculate_page_rank(15)
    # graph.print_scores()


if __name__ == '__main__':
    main()
