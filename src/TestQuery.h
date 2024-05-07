#include <iostream>
#include <string>
#include "Graph.h"
#include "LocationQuery.h"
void QueryTest() {
    Graph g(21);

    // 添加节点
    g.addNode(0, Node::Type::BUILDING, "入口大门", "大门");
    g.addNode(1, Node::Type::FACILITY, "咖啡店", "餐饮");
    g.addNode(2, Node::Type::BUILDING, "教学楼A", "教学楼");
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
    g.addEdge(0, 1, 101, 0.1, 40);
    g.addEdge(0, 2, 15, 0.5, 40);
    g.addEdge(1, 3, 35, 0.9, 30);
    g.addEdge(1, 4, 78, 0.2, 35);
    g.addEdge(2, 6, 60, 0.4, 20);
    g.addEdge(3, 5, 500, 0.0, 40);
    g.addEdge(4, 5, 24, 0.1, 5);
    g.addEdge(6, 7, 100, 0.9, 150);
    g.addEdge(5, 7, 80, 0.2, 40);
    g.addEdge(3, 4, 200, 0.1, 40);
    g.addEdge(3, 5, 150, 0.2, 35);
    g.addEdge(4, 6, 120, 0.3, 30);
    g.addEdge(4, 7, 86, 0.1, 45);
    g.addEdge(5, 8, 95, 0.2, 40);
    g.addEdge(5, 9, 79, 0.4, 35);
    g.addEdge(6, 10, 50, 0.1, 50);
    g.addEdge(6, 11, 60, 0.4, 45);
    g.addEdge(7, 12, 100, 0.2, 4);
    g.addEdge(7, 13, 124, 0.1, 45);
    g.addEdge(8, 14, 80, 0.3, 30);
    g.addEdge(8, 15, 110, 0.2, 35);
    g.addEdge(9, 16, 70, 0.1, 40);
    g.addEdge(9, 17, 90, 0.4, 45);
    g.addEdge(10, 18, 67, 0.3, 50);
    g.addEdge(10, 19, 40, 0.2, 45);
    g.addEdge(11, 20, 125, 0.1, 45);
    g.addEdge(11, 12, 80, 0.3, 35);
    g.addEdge(12, 13, 50, 0.2, 90);
    g.addEdge(12, 14, 120, 0.9, 50);
    g.addEdge(13, 15, 90, 0.4, 35);
    g.addEdge(13, 16, 78, 0.9, 70);
    g.addEdge(14, 17, 110, 0.2, 45);
    g.addEdge(14, 18, 80, 0.0, 50);
    g.addEdge(15, 19, 120, 0.3, 55);
    g.addEdge(15, 20, 100, 0.7, 40);

    // 创建LocationQuery对象，关联到已有的图
    LocationQuery query(g);

    // 载入场所数据
    query.loadFacilities();

    // 设定起始位置节点，假设以节点ID为1的位置为起点查询附近设施
    std::cout << "请输入当前位置的节点ID: ";
    int startNodeId;
    std::cin >> startNodeId;
    Node* startLocation = g.getNode(startNodeId);
    std::cout << "当前位置为: " << startLocation->getName() << std::endl;

    // 查询指定公里内的设施
    std::cout << "Please input the search radius (in meters): ";
    double searchRadius;
    std::cin >> searchRadius;
    // double searchRadius = 1000;  // 单位为米（或者与Node类位置单位相同）
    auto nearbyFacilities = query.findNearbyFacilities(startLocation, searchRadius);

    query.sortFacilitiesByDistance(nearbyFacilities, 0, nearbyFacilities.size() - 1);

    // 输出查询结果
    std::cout << "Facilities within " << searchRadius << " m radius:" << std::endl;
    for (const auto& facility : nearbyFacilities) {
        std::cout << "Facility Name: " << facility->getName() << "    Distance: " << facility->getDistance() << " meters" << std::endl;
    }

    // 过滤查询结果
    // std::cout << "\nPlease input the interested facility type: ";
    // std::string interestedType;
    // std::cin >> interestedType;
    std::string interestedType = "餐饮";
    auto filteredFacilities = query.filterResultsByCategory(nearbyFacilities, interestedType);

    // 输出过滤后的结果
    std::cout << "\nFiltered Facilities (Type - " << interestedType << "):" << std::endl;
    for (const auto& facility : filteredFacilities) {
        std::cout << "Facility Name: " << facility->getName() << "    Distance: " << facility->getDistance() << " meters" << std::endl;
    }

    std::string interestedType1 = "卫生间";
    auto filteredFacilities1 = query.filterResultsByCategory(nearbyFacilities, interestedType1);

    // 输出过滤后的结果
    std::cout << "\nFiltered Facilities (Type - " << interestedType1 << "):" << std::endl;
    for (const auto& facility : filteredFacilities1) {
        std::cout << "Facility Name: " << facility->getName() << "    Distance: " << facility->getDistance() << " meters" << std::endl;
    }
}