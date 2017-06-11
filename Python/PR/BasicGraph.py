import time

class BasicGraph:
    def __init__(self):
        self.adjList = dict()

    def add_edge(self, src, dest):
        if src not in self.adjList:
            self.adjList[src] = AdjList()
        self.adjList[src].out += 1
        if dest not in self.adjList:
            self.adjList[dest] = AdjList()
        self.adjList[dest].aList.append(src)

    def calculate_page_rank(self, iterations):
        d = 0.85
        n = len(self.adjList)
        sink_nodes = []
        npg = dict()
        for node in self.adjList:
            self.adjList[node].pr = 1.0 / n
            if self.adjList[node].out == 0:
                sink_nodes.append(node)
        num = iterations
        while iterations > 0:
            start = time.time()
            sink_node_rank = 0
            for node in sink_nodes:
                sink_node_rank += self.adjList[node].pr
            for node in self.adjList:
                npg[node] = (1.0 - d) / n
                npg[node] += (d * sink_node_rank) / n
                for inNode in self.adjList[node].aList:
                    npg[node] += ((d * self.adjList[inNode].pr) / self.adjList[inNode].out)
            for node in self.adjList:
                self.adjList[node].pr = npg[node]
            iterations -= 1
            end = time.time() - start
            print("Iteration " + str(num - iterations)) + " completed in " + str(end * 1000) + "ms"

    def print_graph(self):
        for node in self.adjList:
            print("Inverted AdjList for Vertex " + node)
            print("Out: " + str(self.adjList[node].out))
            for inNode in self.adjList[node].aList:
                print " <-" + inNode,
            print('')

    def print_scores(self):
        total = 0
        for node in self.adjList:
            print(node + "\t" + str(self.adjList[node].pr))
            total += self.adjList[node].pr
        print("Sum: " + str(total))


class AdjList:
    def __init__(self):
        self.pr = 0
        self.out = 0
        self.aList = []
