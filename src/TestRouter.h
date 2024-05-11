#include <iomanip>
#include <iostream>
#include <string>
#include "Algorithms.h"
#include "Graph.h"
#include "include/mysql.h"

void RouterTest() {
    Graph g(200);
    /*
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
    */
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
    mysql_query(&my_sql, "select * from nodes;");

    // 获取结果集
    int count = 0;
    res = mysql_store_result(&my_sql);
    while (row = mysql_fetch_row(res)) {
        // std::cout << "row:" << row[0] << " " << row[1] << " " << row[2] << std::endl;
        int id = std::stoi(row[0]);
        int type1 = std::stoi(row[1]);
        Node::Type type = static_cast<Node::Type>(type1);
        // std::cout << id << " " << type << " " << row[2] << std::endl;
        g.addNode(id, type, row[2], row[3]);
        count++;
    }
    g.size = count;

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

    // 选择路线规划/多个途径点规划
    std::cout << "请输入路线规划方式（1-选择路线规划，2-多个途径点规划）：";
    int mode;
    std::cin >> mode;
    if (mode == 1) {
        // 选择路线规划
        // 用户输入
        std::cout << "请输入起点和终点：" << std::endl;
        int from, to;
        std::cin >> from >> to;

        Node* n1 = g.getNode(from);
        Node* n2 = g.getNode(to);
        std::cout << "起点：" << n1->getName() << "\n终点：" << n2->getName() << std::endl;

        // 使用算法寻找最短路径
        Algorithms::PathResult shortestPathResult = Algorithms::findShortestPath(g, from, to);

        // 打印结果
        std::cout << "Shortest path length: " << shortestPathResult.length << " meters" << std::endl;
        int flag = 0;
        for (int nodeID : shortestPathResult.path) {
            if (flag == 0) {
                std::cout << nodeID;
                flag = 1;
            } else {
                std::cout << " --> " << nodeID;
            }
        }
        std::cout << std::endl;

        // 使用算法寻找最快路径
        Algorithms::PathResult fastestPathResult = Algorithms::findFastestPath(g, from, to);

        // 输出结果
        std::cout << "Fastest path time: " << std::fixed << std::setprecision(1) << fastestPathResult.time << " minutes" << std::endl;
        flag = 0;
        for (int nodeID : fastestPathResult.path) {
            if (flag == 0) {
                std::cout << nodeID;
                flag = 1;
            } else {
                std::cout << " --> " << nodeID;
            }
        }
        std::cout << std::endl;
    } else {
        std::vector<int> targets;

        std::cout << "请输入当前位置id：";
        int start;
        std::cin >> start;
        // targets.push_back(start);

        std::cout << "请输入途径点(输入-1结束):" << std::endl;
        int target;
        while (std::cin >> target && target != -1) {
            targets.push_back(target);
        }

        // 使用暴力算法
        Algorithms::PathResult fspPathResult = Algorithms::findBruteForcePath(g, start, targets);

        // 输出结果
        std::cout << "Shortest path length: " << fspPathResult.length << " meters" << std::endl;
        int flag = 0;
        for (int nodeID : fspPathResult.path) {
            if (flag == 0) {
                std::cout << nodeID;
                flag = 1;
            } else {
                std::cout << " --> " << nodeID;
            }
        }
        std::cout << std::endl;
        /*
                // 生成距离矩阵
                auto dist = g.generateDistanceMatrix();

                // 使用算法寻找最短路径
                Algorithms::PathResult TspPathResult = Algorithms::findTspPath(dist, start, targets);

                // 打印结果
                std::cout << "Shortest path length: " << TspPathResult.length << " meters" << std::endl;
                int flag = 0;
                for (int nodeID : TspPathResult.path) {
                    if (flag == 0) {
                        std::cout << nodeID;
                        flag = 1;
                    } else {
                        std::cout << " --> " << nodeID;
                    }
                }
                std::cout << std::endl;
            */
    }
}