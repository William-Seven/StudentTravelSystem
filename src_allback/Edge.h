// 文件说明: 定义边的基本属性和方法。
// 基本属性包括：起点，终点，距离长度，拥挤度，交通方式，理想速度

#ifndef EDGE_H
#define EDGE_H

#include <string>
#include "Node.h"

class Edge {
   public:
    // 交通工具类型
    enum type {
        WALK = 1,
        BIKE = 2,
        EBIKE = 3
    };

    Node* source;        // 边的起点节点
    Node* destination;   // 边的终点节点
    double distance;     // 边的长度
    double congestion;   // 边的拥挤度
    type transportMode;  // 边的交通工具类型
    double speed;        // 边的交通工具速度

    // 构造函数
    Edge(Node* source, Node* destination, double distance, double congestion, type transportMode, double speed);

    // 获取边的起点节点
    Node* getFrom() const;

    // 获取边的终点节点
    Node* getTo() const;

    // 获取边的长度
    double getLength() const;

    // 获取边的拥挤度
    double getCongestion() const;

    // 获取边的交通工具类型
    // const std::string& getRoadType() const;

    // 获取边的交通工具速度
    double getSpeed() const;

    // 获取交通工具类型
    type gettype() const;
};

#endif  // EDGE_H