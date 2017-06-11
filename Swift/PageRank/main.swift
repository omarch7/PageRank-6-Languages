//
//  main.swift
//  PageRank
//
//  Created by 奥玛 on 4/14/16.
//  Copyright © 2016 THU. All rights reserved.
//

import Foundation

let graph = BasicGraph()

let start = NSDate()
if let aStreamReader = StreamReader(path: "/Users/omar/Documents/Tsinghua/Spring 2016/CPP/PageRank/linkgraph.txt"){
    defer {
        aStreamReader.close()
    }
    while let line = aStreamReader.nextLine(){
        var values = line.componentsSeparatedByString("\t")
        graph.addEdge(Int(values[0])!, dest: Int(values[1])!)
    }
}
let end = NSDate()
let timeInterval: Double = end.timeIntervalSinceDate(start)
print("Loaded into memory in \(timeInterval * 1000)ms")

let totalStart = NSDate()
graph.calculatePageRank(15)
let totalEnd = NSDate()
let totalTimeInterval: Double = totalEnd.timeIntervalSinceDate(totalStart)
print("Total running time \(totalTimeInterval * 1000)ms")

//graph.printScores()