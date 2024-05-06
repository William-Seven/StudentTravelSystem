// 文件说明：定义图的数据结构和基本方法

#ifndef GRAPH_H
#define GRAPH_H

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
    void addEdge(const int& from, const int& to, double distance, double congestion, double speed, TransportMode transportMode = TransportMode::WALK);

    // 获取节点
    Node* getNode(int id);
};

#endif  // GRAPH_H