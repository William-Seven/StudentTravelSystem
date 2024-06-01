// 文件说明：最短路径、最快路径的算法实现（Dijkstra 算法）

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include "Graph.h"
#include "MyHashMap.h"

class Algorithms {
   public:
    // 定义结构体存储Dijkstra算法的结果，包括路径和路径长度
    struct PathResult {
        std::vector<int> path;  // 存储最短路径的途径点序列
        double length;          // 存储最短路径的总长度
        double time;            // 存储最快路径的总时间

        PathResult()
            : length(0), time(0) {}
    };

    // Dijkstra算法，计算最短路径
    static PathResult findShortestPath(Graph& graph, int startNodeID, int endNodeID);

    // Dijkstra算法，计算最快路径
    static PathResult findFastestPath(Graph& graph, int startNodeID, int endNodeID, int mode);

    // 暴力算法，全排列
    static PathResult findBruteForcePath(Graph& graph, int startNodeID, std::vector<int>& targets);

    // 模拟退火
    static PathResult simulatedAnnealing(Graph& completeGraph, int startNodeID, std::vector<int>& nodes);

    // 构造完全图并使用模拟退火算法
    static PathResult findOptimalPath(Graph& graph, int startNodeID, std::vector<int>& targets);
};

#endif  // ALGORITHMS_H