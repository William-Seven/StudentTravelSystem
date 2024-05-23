// 文件说明：定义图的数据结构和基本方法

#ifndef GRAPH_H
#define GRAPH_H

#include <limits>
#include <vector>
#include "Edge.h"
#include "MyHashMap.h"
#include "Node.h"

class Graph {
   public:
    int size;
    HashMap<int, Node*, HashFunc> nodes;  // 存储图里的所有节点

    Graph(int size);
    ~Graph();

    // 添加节点
    void addNode(int id, Node::Type type, const std::string& name, const std::string& description);

    // 添加边
    // void addEdge(const int& from, const int& to, double distance);
    void addEdge(const int& from, const int& to, double distance, double congestion, double speed, Edge::type transportMode);

    // 获取节点
    Node* getNode(int id);

    // 生成图的距离矩阵，用于存储节点之间的距离
    std::vector<std::vector<double>> generateDistanceMatrix();
};

#endif  // GRAPH_H