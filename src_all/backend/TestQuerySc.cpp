#include <iostream>
#include <string>
#include "Graph.h"
#include "LocationQuery.h"
#include "include/mysql.h"

int main(int argc, char* argv[]) {
    Graph g(200);

    MYSQL my_sql;
    MYSQL_RES* res;  // 查询结果集
    MYSQL_ROW row;   // 记录结构体

    // 初始化数据库
    mysql_init(&my_sql);

    // 连接数据库
    if (!mysql_real_connect(&my_sql, "localhost", "root", "abc123", "test3", 3306, NULL, 0)) {
        std::cout << "错误原因：" << mysql_error(&my_sql) << std::endl;
        std::cout << "连接数据库失败" << std::endl;
        exit(-1);
    }

    // 查询nodes
    mysql_query(&my_sql, "select * from nodessc;");

    // 获取结果集
    int count = 0;
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        int id = std::stoi(row[0]);
        int type1 = std::stoi(row[1]);
        Node::Type type = static_cast<Node::Type>(type1);
        g.addNode(id, type, row[2], row[3]);
        count++;
    }
    g.size = count;

    // 查询edge
    mysql_query(&my_sql, "select * from edgesc;");

    // 获取结果集
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        int start = std::stoi(row[0]);
        int end = std::stoi(row[1]);
        double distance = std::stod(row[2]);
        double congestion = std::stod(row[3]);
        double speed = std::stod(row[4]);
        Edge::type type = static_cast<Edge::type>(std::stoi(row[5]));
        g.addEdge(start, end, distance, congestion, speed, type);
    }

    // 创建LocationQuery对象，关联到已有的图
    LocationQuery query(g);

    // 载入场所数据
    query.loadFacilities();

    // 设定起始位置节点
    int startNodeId = std::stoi(argv[1]);

    Node* startLocation = g.getNode(startNodeId);
    std::cout << startLocation->getName() << "\n";

    // 查询指定距离（米）内的设施
    double searchRadius = std::stod(argv[2]);
    std::string interestedType = argv[3];

    auto nearbyFacilities = query.findNearbyFacilities(startLocation, searchRadius);
    query.sortFacilitiesByDistance(nearbyFacilities, 0, nearbyFacilities.size() - 1);

    if (interestedType == "all") {
        // 输出查询结果
        for (const auto& facility : nearbyFacilities) {
            std::cout << facility->getId() << " " << facility->getName() << " " << facility->getDescription() << " " << facility->getDistance() << "\n";
        }
    } else {
        // 过滤查询结果
        auto filteredFacilities = query.filterResultsByCategory(nearbyFacilities, interestedType);

        // 输出过滤后的结果
        for (const auto& facility : filteredFacilities) {
            std::cout << facility->getId() << " " << facility->getName() << " " << facility->getDescription() << " " << facility->getDistance() << "\n";
        }
    }
}