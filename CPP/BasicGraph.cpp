//
// Created by 奥玛 on 4/8/16.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include "BasicGraph.h"

void BasicGraph::addEdge(int src, int dest) {
    ++map[src].out;
    map[dest].list.emplace_back(src);
}

void BasicGraph::calculatePageRank(int iteration, bool print) {
    struct timeval tp_begin, tp_scan;
    float d = 0.85;
    float N = float(map.size());
    float restartRate = (1.0f-d) / N;
    std::unordered_map<int, float> npg;
    std::vector<int> sinkNodes;
    for(auto iterator = map.begin(); iterator!= map.end(); iterator++){
        map[iterator->first].pr = 1.0f / N;
        if(map[iterator->first].out==0){
            sinkNodes.emplace_back(iterator->first);
        }
    }
    int num = iteration;

    while(iteration>0){
        gettimeofday(&tp_begin, NULL);
        float sinkNodesRank = 0.0f;
        for(auto&& node : sinkNodes){
            sinkNodesRank += map[node].pr;
        }
        for(auto iterator = map.begin(); iterator != map.end(); iterator++){
            float pageRank = restartRate + (d * sinkNodesRank) / N;
//            npg[iterator->first] = restartRate;
//            npg[iterator->first] += (d * sinkNodesRank) / N;
            for(auto&& node : map[iterator->first].list){
                pageRank += ((d * map[node].pr) / map[node].out);
//                npg[iterator->first] += ((d * map[node].pr) / map[node].out);
            }
            npg[iterator->first] = pageRank;
        }
        for(auto iterator = map.begin(); iterator != map.end(); iterator++){
            map[iterator->first].pr = npg[iterator->first];
        }
        gettimeofday(&tp_scan, NULL);
        int elapsed_time = tp_scan.tv_usec - tp_begin.tv_usec;
        elapsed_time += 1000000*(tp_scan.tv_sec - tp_begin.tv_sec);
        if(print){
            std::cout << "Iteration " << num - iteration + 1 << " completed in " << float(elapsed_time) / 1000 << "ms" << std::endl;
        }
        --iteration;
    }
}

void BasicGraph::printGraph() {
    for(auto iterator = map.begin(); iterator != map.end(); iterator++){
        std::cout << "Adjacency List of Vertex " << iterator->first << std::endl;
        std::cout << "Out: " << map[iterator->first].out << "\nin-head";
        for(auto&& node : map[iterator->first].list){
            std::cout << " <-" << node;
        }
        std::cout << std::endl;
    }
}

void BasicGraph::printScores() {
    float check = 0;
    for(auto iterator = map.begin(); iterator != map.end(); iterator++){
        std::cout << iterator->first << "\t" << map[iterator->first].pr << std::endl;
        check += map[iterator->first].pr;
    }
    std::cout << "Sum: " << check << std::endl;
}

void BasicGraph::saveOutput(std::string filename) {
    std::ofstream out(filename);
    std::map<int, AdjList> ordered(map.begin(), map.end());
    for(auto iterator = ordered.begin(); iterator != ordered.end(); iterator++){
        out << iterator->first << "\t" << this->convert(ordered[iterator->first].pr) << "\n";
    }
    out.close();
}

std::string BasicGraph::convert(float value) {
    std::stringstream ss;
    ss << std::setprecision(std::numeric_limits<float>::digits10+1);
    ss << value;
    return ss.str();
}