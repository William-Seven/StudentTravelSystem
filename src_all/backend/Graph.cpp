#include "Graph.h"

#define DNF std::numeric_limits<double>::max()  // 定义一个无限大的值用于表示无法到达

// 构造函数
Graph::Graph(int size)
    : size(size), nodes(size) {}

// 添加节点
void Graph::addNode(int id, Node::Type type, const std::string& name, const std::string& description) {
    if (nodes.find(id) == nullptr) {
        Node* newNode = new Node(id, type, name, description);
        nodes.insert(id, newNode);
    } else {
        std::cout << nodes.find(id) << std::endl;
        std::cout << nodes[id]->id << std::endl;
        // 节点已存在，打印错误信息
        std::cout << "Node with id " << id << " already exists!" << std::endl;
    }
}

void Graph::addEdge(const int& from, const int& to, double distance, double congestion, double speed, Edge::type transportMode) {
    Node* sourceNode = getNode(from);     // 获取源节点
    Node* destinationNode = getNode(to);  // 获取目标节点

    if (sourceNode && destinationNode) {
        // 添加从from到to的边
        Edge* newEdge = new Edge(sourceNode, destinationNode, distance, congestion, transportMode, speed);
        sourceNode->addEdge(newEdge);  // 将该边添加到源节点的边列表中

        // 无向图，添加从to到from的边
        Edge* newEdge2 = new Edge(destinationNode, sourceNode, distance, congestion, transportMode, speed);
        destinationNode->addEdge(newEdge2);  // 将该边添加到目标节点的边列表中
    } else {
        std::cout << "Either source or destination node does not exist." << std::endl;
    }
}

// 获取节点
Node* Graph::getNode(int id) {
    return *(nodes.find(id));
}