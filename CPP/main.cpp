#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include "BasicGraph.h"

using namespace std;

string getPath(){
    char buffer[FILENAME_MAX];
    char *answer = getcwd(buffer, sizeof(buffer));
    string s_cwd;
    if (answer) {
        s_cwd = answer;
    }
    return s_cwd;
}

void calculatePageRank(){
    struct timeval tp_begin, tp_scan;

    ifstream file;
    string line;

//    string path = getPath() + "/example/ex2/linkgraph.temp.30";
    string path = getPath() + "/linkgraph.txt";

    BasicGraph *graph = new BasicGraph;

    file.open(path);
    if(file.is_open()){
        gettimeofday(&tp_begin, NULL);
        while(getline(file, line)){
            int pos = line.find("\t");
            int src = stoi(line.substr(0, pos));
            int dest = stoi(line.substr(pos + 1));
            graph->addEdge(src, dest);
        }
        file.close();
        gettimeofday(&tp_scan, NULL);
        int elapsed_time = tp_scan.tv_usec - tp_begin.tv_usec;
        elapsed_time += 1000000*(tp_scan.tv_sec - tp_begin.tv_sec);
        std::cout << "Loaded into memory in " << float(elapsed_time) / 1000 << "ms" <<std::endl;

        gettimeofday(&tp_begin, NULL);

        graph->calculatePageRank(5, true);

        gettimeofday(&tp_scan, NULL);

        elapsed_time = tp_scan.tv_usec - tp_begin.tv_usec;
        elapsed_time += 1000000*(tp_scan.tv_sec - tp_begin.tv_sec);
        cout << "Running time: " << float(elapsed_time) / 1000 << "ms" << endl;

        graph->saveOutput("PR_2015280261_5.txt");
//        graph->printScores();

//        graph->printGraph();
    }else{
        std::cout << "Couldn't read file at " << path << std::endl;
    }

}

int main() {
    calculatePageRank();
    return 0;
}