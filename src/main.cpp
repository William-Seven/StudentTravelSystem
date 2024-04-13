#include <iostream>
#include <string>
#include "Algorithms.h"
#include "Graph.h"
#include "include/mysql.h"

int main() {
    // 创建一个图实例
    Graph g(8);  // 假设你的图有8个节点

    /*
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
    */

    MYSQL my_sql;
    MYSQL_RES* res;  // 查询结果集
    MYSQL_ROW row;   // 记录结构体

    // 初始化数据库
    mysql_init(&my_sql);

    // 连接数据库
    if (!mysql_real_connect(&my_sql, "localhost", "root", "abc123", "test2", 3306, NULL, 0)) {
        std::cout << "错误原因：" << mysql_error(&my_sql) << std::endl;
        std::cout << "连接数据库失败" << std::endl;
        exit(-1);
    }

    // 查询nodes
    mysql_query(&my_sql, "select * from nodes;");

    // 获取结果集
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        // std::cout << "row:" << row[0] << " " << row[1] << " " << row[2] << std::endl;
        int id = std::stoi(row[0]);
        int type1 = std::stoi(row[1]);
        Node::Type type = static_cast<Node::Type>(type1);
        // std::cout << id << " " << type << " " << row[2] << std::endl;
        g.addNode(id, type, row[2]);
    }

    // 查询edge
    mysql_query(&my_sql, "select * from edge;");

    // 获取结果集
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        int start = std::stoi(row[0]);
        int end = std::stoi(row[1]);
        double distance = std::stod(row[2]);
        double congestion = std::stod(row[3]);
        double speed = std::stod(row[4]);
        // std::cout << start << " " << end << " " << distance << " " << congestion << " " << speed << std::endl;
        g.addEdge(start, end, distance, congestion, speed);
    }

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

    mysql_free_result(res);
    mysql_close(&my_sql);
    return 0;
}
