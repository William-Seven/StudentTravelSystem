// 文件说明：定义节点的基本属性和方法。每个节点可以代表一个景点或建筑。
// 每个节点代表一个景点或建筑
// 基本属性包括：id，名称，类型，路径，相关描述

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Edge;  // 前向声明

class Node {
   public:
    // 节点类型枚举
    enum Type {
        BUILDING,  // 建筑、景点、场所
        FACILITY,  // 设施
        NONE
    };

    int id;                    // 节点的唯一标识
    Type type;                 // 节点的类型
    std::string name;          // 节点的名称
    std::vector<Edge*> edges;  // 与该节点相连的边
    std::string description;   // 节点的描述信息

    // 构造函数
    Node(int id, Type type, const std::string& name, const std::string& description = "");

    // 析构函数
    ~Node();  // 释放edges中的边指针

    // 获取节点ID
    int getId() const;

    // 获取节点名称
    const std::string& getName() const;

    // 获取节点类型
    Type getType() const;

    // 获取节点描述
    const std::string& getDescription() const;

    // 设置节点描述
    void setDescription(const std::string& description);

    // 添加边
    void addEdge(Edge* edge);

    // 静态方法，用于创建表示“空”的Node实例
    static Node emptyNode();
};

#endif  // NODE_H