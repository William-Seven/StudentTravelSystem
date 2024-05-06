#include <iostream>
#include <string>
#include "Algorithms.h"
#include "Graph.h"

void RouterTest() {
    Graph g(21);

    // 添加节点
    g.addNode(0, Node::Type::BUILDING, "入口大门", "大门");
    g.addNode(1, Node::Type::BUILDING, "教学楼A", "教学楼");
    g.addNode(2, Node::Type::FACILITY, "咖啡店", "餐饮");
    g.addNode(3, Node::Type::FACILITY, "超市1号", "超市");
    g.addNode(4, Node::Type::BUILDING, "图书馆", "图书馆");
    g.addNode(5, Node::Type::FACILITY, "卫生间2号", "卫生间");
    g.addNode(6, Node::Type::BUILDING, "实验楼A", "实验楼");
    g.addNode(7, Node::Type::FACILITY, "饭店1号", "餐饮");
    g.addNode(8, Node::Type::BUILDING, "学生宿舍1栋", "宿舍");
    g.addNode(9, Node::Type::FACILITY, "医务室", "医务室");
    g.addNode(10, Node::Type::BUILDING, "艺术中心", "艺术中心");
    g.addNode(11, Node::Type::FACILITY, "体育馆", "体育馆");
    g.addNode(12, Node::Type::BUILDING, "教学楼B", "教学楼");
    g.addNode(13, Node::Type::FACILITY, "超市2号", "超市");
    g.addNode(14, Node::Type::BUILDING, "图书馆副楼", "图书馆");
    g.addNode(15, Node::Type::FACILITY, "卫生间3号", "卫生间");
    g.addNode(16, Node::Type::BUILDING, "实验楼B", "实验楼");
    g.addNode(17, Node::Type::FACILITY, "饭店2号", "餐饮");
    g.addNode(18, Node::Type::BUILDING, "学生宿舍2栋", "宿舍");
    g.addNode(19, Node::Type::FACILITY, "洗衣房", "洗衣房");
    g.addNode(20, Node::Type::BUILDING, "行政楼", "行政楼");

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
    g.addEdge(3, 4, 100, 0.1, 40);
    g.addEdge(3, 5, 150, 0.2, 35);
    g.addEdge(4, 6, 120, 0.3, 30);
    g.addEdge(4, 7, 80, 0.1, 45);
    g.addEdge(5, 8, 90, 0.2, 40);
    g.addEdge(5, 9, 70, 0.4, 35);
    g.addEdge(6, 10, 50, 0.1, 50);
    g.addEdge(6, 11, 60, 0.3, 45);
    g.addEdge(7, 12, 100, 0.2, 40);
    g.addEdge(7, 13, 120, 0.1, 45);
    g.addEdge(8, 14, 80, 0.3, 30);
    g.addEdge(8, 15, 110, 0.2, 35);
    g.addEdge(9, 16, 70, 0.1, 40);
    g.addEdge(9, 17, 90, 0.4, 45);
    g.addEdge(10, 18, 60, 0.3, 50);
    g.addEdge(10, 19, 40, 0.2, 45);
    g.addEdge(11, 20, 100, 0.1, 40);
    g.addEdge(11, 12, 80, 0.3, 35);
    g.addEdge(12, 13, 50, 0.2, 40);
    g.addEdge(12, 14, 120, 0.1, 50);
    g.addEdge(13, 15, 90, 0.4, 35);
    g.addEdge(13, 16, 70, 0.3, 40);
    g.addEdge(14, 17, 110, 0.2, 45);
    g.addEdge(14, 18, 80, 0.1, 50);
    g.addEdge(15, 19, 120, 0.3, 35);
    g.addEdge(15, 20, 100, 0.2, 40);

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
}