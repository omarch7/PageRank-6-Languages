/**
 * Created by omar on 4/13/16.
 */

readline = require('readline');
fs = require('fs');

var rl = readline.createInterface({
    // input: fs.createReadStream('examples/ex3/linkgraph.temp.100')
    input: fs.createReadStream('/Users/omar/Documents/Tsinghua/Spring 2016/CPP/PageRank/linkgraph.txt')
});



var AdjList = function () {
    this.numOut = 0;
    this.pr = 0;
    this.aList = [];
}

var BasicGraph = function () {
    this.adjList = {};
}

BasicGraph.prototype.addEdge = function (src, dest) {
    if(!this.adjList.hasOwnProperty(src)){
        this.adjList[src] = new AdjList();
    }
    this.adjList[src].numOut++;
    if(!this.adjList.hasOwnProperty(dest)){
        this.adjList[dest] = new AdjList();
    }
    this.adjList[dest].aList.push(src);
}

BasicGraph.prototype.calculatePageRank = function (iterations) {
    var d = 0.85;
    var N = parseFloat(Object.keys(this.adjList).length);
    var npg = {};
    var sinkNodes = [];
    for(var node in this.adjList){
        if(this.adjList.hasOwnProperty(node)){
            this.adjList[node].pr = 1.0 / N;
            if(this.adjList[node].numOut==0){
                sinkNodes.push(node);
            }
        }
    }
    var num = iterations;
    while(iterations>0){
        console.time("timer");
        var sinkNodesRank = 0;
        var self = this;
        sinkNodes.forEach(function (sinkNode) {
            sinkNodesRank += self.adjList[sinkNode].pr;
        });
        for(var node in this.adjList){
            if(this.adjList.hasOwnProperty(node)){
                npg[node] = (1.0 - d) / N;
                npg[node] += (d * sinkNodesRank) / N;
                var self = this;
                this.adjList[node].aList.forEach(function (inNode) {
                    npg[node] += ((d * self.adjList[inNode].pr) / self.adjList[inNode].numOut);
                });
            }
        }
        for(var node in this.adjList){
            if(this.adjList.hasOwnProperty(node)){
                this.adjList[node].pr = npg[node];
            }
        }
        --iterations;
        process.stdout.write("Iteration " + (num - iterations) + " completed in ");
        console.timeEnd("timer");
    }

}

BasicGraph.prototype.printScores = function () {
    var sum = 0;
    for(var node in this.adjList){
        if(this.adjList.hasOwnProperty(node)){
            console.log(node + '\t' + this.adjList[node].pr);
            sum += this.adjList[node].pr;
        }
    }
    console.log('Sum: ' + sum);
}

BasicGraph.prototype.printGraph = function () {
    for(var node in this.adjList){
        if(this.adjList.hasOwnProperty(node)){
            console.log('Inverted AdjList for Vertex ' +node);
            console.log('Out: '+ this.adjList[node].numOut);
            this.adjList[node].aList.forEach(function (inNode) {
                process.stdout.write(' <-'+inNode);
            });
            console.log('');
        }
    }
}

var graph = new BasicGraph();
console.time("load");
rl.on('line', function (line) {
    var links = line.split('\t');
    graph.addEdge(parseInt(links[0]), parseInt(links[1]));
}).on('close', function () {
    console.timeEnd("load");
    console.time("total");
    graph.calculatePageRank(15);
    console.timeEnd("total");
    // graph.printGraph();
    // graph.printScores();
});