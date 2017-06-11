//
//  BasicGraph.swift
//  PageRank
//
//  Created by 奥玛 on 4/14/16.
//  Copyright © 2016 THU. All rights reserved.
//

import Foundation

struct AdjList {
    var pr: Float = 0.0
    var out: Int = 0
    var inList: Array = [Int]()
}

class BasicGraph {
    var map: [Int: AdjList] = [:]
    
    func addEdge(src: Int, dest: Int) -> Void {
        if(map[src]==nil){
            map[src] = AdjList()
        }
        map[src]?.out += 1
        if(map[dest]==nil){
            map[dest] = AdjList()
        }
        map[dest]?.inList.append(src)
    }
    
    func calculatePageRank(iterations: Int) -> Void {
        let d: Float = 0.85
        let N: Float = Float(map.count)
        let restartRate = (1.0 - d) / N
        var sinkNodes: Array = [Int]()
        var newPageRank: [Int: Float] = [:]
        for (key, node) in map {
            map[key]?.pr = 1.0 / N
            if(node.out==0){
                sinkNodes.append(key)
            }
        }
        var num = iterations
        while num > 0 {
            let start = NSDate()
            var sinkNodeRank: Float = 0
            for node in sinkNodes {
                sinkNodeRank += (map[node]?.pr)!
            }
            for (key, node) in map {
                var npg: Float = restartRate
                npg += (d * sinkNodeRank) / N
                for inNode in node.inList {
                    npg += ((d * map[inNode]!.pr) / Float(map[inNode]!.out))
                }
                newPageRank[key] = npg
            }
            for (key, _) in map {
                map[key]!.pr = newPageRank[key]!
            }
            num -= 1
            let end = NSDate()
            let timeInterval: Double = end.timeIntervalSinceDate(start)
            print("Iteration \(iterations - num) completed in \(timeInterval * 1000)")
        }
    }
    
    func printScores() -> Void {
        for (key, node) in map {
            print("\(key)\t\(node.pr)")
        }
    }
    
    func printGraph() -> Void {
        for (key, node) in map {
            print("Inverted AdjList for vertex \(key) \nOut: \(node.out)")
            for inNode in node.inList {
                print("<- \(inNode) ", terminator:"")
            }
            print("")
        }
    }
}