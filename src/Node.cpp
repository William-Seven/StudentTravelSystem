// Node类型的相关方法实现

#include "Node.h"
#include "Edge.h"

Node::Node(int id, Type type, const std::string& name, const std::string& description)
    : id(id), type(type), name(name), description(description) {}

Node::~Node() {
    // 遍历edges向量，删除每一个Edge对象
    for (Edge* edge : edges)
        delete edge;
    edges.clear();  // 清空向量，显式调用，便于代码理解
}

int Node::getId() const {
    return id;
}

const std::string& Node::getName() const {
    return name;
}

Node::Type Node::getType() const {
    return type;
}

const std::string& Node::getDescription() const {
    return description;
}

void Node::setDescription(const std::string& description) {
    this->description = description;
}

void Node::addEdge(Edge* edge) {
    edges.push_back(edge);
}

Node Node::emptyNode() {
    return Node(-1, NONE, "Empty", "This is an empty node.");
};
Node valuenull = Node::emptyNode();