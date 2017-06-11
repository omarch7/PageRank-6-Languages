//
// Created by 奥玛 on 4/8/16.
//

#ifndef PAGERANK_BASICGRAPH_H
#define PAGERANK_BASICGRAPH_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>

struct AdjList{
    int out = 0;
    float pr = 0;
    std::vector<int> list;
};

struct Page{
    int id = 0;
    float pr = 0.0f;
};

class BasicGraph {
private:
    std::unordered_map<int, AdjList> map;
    std::string convert(float value);
public:
    void addEdge(int src, int dest);
    void calculatePageRank(int iteration, bool print);
    void printGraph();
    void printScores();
    void saveOutput(std::string filename);
};


#endif //PAGERANK_BASICGRAPH_H
