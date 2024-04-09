#include "Algorithms.h"
#include "Graph.h"

int main() {
    // 创建一个图实例
    Graph g(8);  // 假设你的图有8个节点

    // 添加节点
    g.addNode(0, Node::Type::BUILDING, "入口大门");
    g.addNode(1, Node::Type::BUILDING, "图书馆");
    g.addNode(2, Node::Type::BUILDING, "咖啡店");
    g.addNode(3, Node::Type::BUILDING, "实验室");
    g.addNode(4, Node::Type::BUILDING, "教学楼");
    g.addNode(5, Node::Type::BUILDING, "管理楼");
    g.addNode(6, Node::Type::BUILDING, "学生宿舍");
    g.addNode(7, Node::Type::BUILDING, "体育馆");

    // 添加边，包括距离、拥挤度和速度
    g.addEdge(0, 1, 100, 0.1, 40);
    g.addEdge(0, 2, 50, 0.2, 40);
    g.addEdge(1, 3, 30, 0.3, 30);
    g.addEdge(1, 4, 70, 0.2, 35);
    g.addEdge(2, 6, 60, 0.4, 30);
    g.addEdge(3, 5, 50, 0.1, 40);
    g.addEdge(4, 5, 20, 0.1, 45);
    g.addEdge(6, 7, 100, 0.9, 50);
    g.addEdge(5, 7, 80, 0.2, 40);

    // 使用算法寻找最短路径
    Algorithms::PathResult shortestPathResult = Algorithms::findShortestPath(g, 0, 7);

    // 打印结果
    std::cout << "Shortest path length: " << shortestPathResult.length << std::endl;
    for (int nodeID : shortestPathResult.path) {
        std::cout << nodeID << " ";
    }
    std::cout << std::endl;

    // 使用算法寻找最快路径
    Algorithms::PathResult fastestPathResult = Algorithms::findFastestPath(g, 0, 7);

    // 输出结果
    std::cout << "Fastest path time: " << fastestPathResult.time << std::endl;
    for (int nodeID : fastestPathResult.path)
        std::cout << nodeID << " ";
    std::cout << std::endl;

    return 0;
}
