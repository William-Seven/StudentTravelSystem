#include <iomanip>
#include <iostream>
#include <string>
#include "Algorithms.h"
#include "Graph.h"
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

    // 路线规划方式（1-选择路线规划，2-多个途径点规划）
    std::string mode = argv[3];
    if (mode == "1") {
        // 用户输入
        // 输入起点和终点
        int from, to;
        from = std::stoi(argv[4]);
        to = std::stoi(argv[5]);

        Node* n1 = g.getNode(from);
        Node* n2 = g.getNode(to);
        std::cout << "起点：" << n1->getName() << "\n终点：" << n2->getName() << "\n";

        // 使用算法寻找最短路径
        Algorithms::PathResult shortestPathResult = Algorithms::findShortestPath(g, from, to);

        // 打印结果
        std::cout << "最短路径长度: " << shortestPathResult.length << " 米\n";
        int flag = 0;
        for (int nodeID : shortestPathResult.path) {
            if (flag == 0) {
                Node* ntemp = g.getNode(nodeID);
                std::cout << nodeID << ". " << ntemp->getName();
                flag = 1;
            } else {
                Node* ntemp = g.getNode(nodeID);
                std::cout << " --> " << nodeID << ". " << ntemp->getName();
            }
        }
        std::cout << "\n";

        // 选择最快路径的交通方式(1-walk, 2-ebike, 3-bike)
        int transport;

        std::string temps = argv[2];

        if (temps == "walk") {
            transport = 1;
        } else if (temps == "ebike") {
            transport = 2;
        } else if (temps == "bike") {
            transport = 3;
        } else {
            transport = 1;
        }

        // 使用算法寻找最快路径
        Algorithms::PathResult fastestPathResult = Algorithms::findFastestPath(g, from, to, transport);

        // 输出结果
        std::cout << "最快路径耗时: " << std::fixed << std::setprecision(1) << fastestPathResult.time << " 分钟\n";
        flag = 0;
        for (int nodeID : fastestPathResult.path) {
            if (flag == 0) {
                Node* ntemp = g.getNode(nodeID);
                std::cout << nodeID << ". " << ntemp->getName();
                flag = 1;
            } else {
                Node* ntemp = g.getNode(nodeID);
                std::cout << " --> " << nodeID << ". " << ntemp->getName();
            }
        }
        // std::cout << "\n";
    } else {
        std::vector<int> targets;

        // std::cout << "请输入当前位置id：";
        int start = std::stoi(argv[4]);

        Node* t = g.getNode(start);
        std::cout << "当前位置为：" << t->getName() << "\n";
        // targets.push_back(start);

        // 输入途径点
        std::cout << "途径：";
        for (int i = 5; i < argc; i++) {
            int target = std::stoi(argv[i]);
            Node* t = g.getNode(target);
            std::cout << t->getName() << "  ";
            targets.push_back(target);
        }

        if (targets.size() <= 5) {
            // 使用暴力算法
            Algorithms::PathResult fspPathResult = Algorithms::findBruteForcePath(g, start, targets);

            // 输出结果
            std::cout << "\n最短路线长度为: " << fspPathResult.length << " 米\n";
            int flag = 0;
            for (int nodeID : fspPathResult.path) {
                if (flag == 0) {
                    Node* ntemp = g.getNode(nodeID);
                    std::cout << nodeID << ". " << ntemp->getName();
                    flag = 1;
                } else {
                    Node* ntemp = g.getNode(nodeID);
                    std::cout << " --> " << nodeID << ". " << ntemp->getName();
                }
            }
            std::cout << "\n";
        } else {
            // 使用启发式算法————模拟退火
            Algorithms::PathResult optimalPath = Algorithms::findOptimalPath(g, start, targets);

            // 输出结果
            std::cout << "\n最短路线长度为: " << optimalPath.length << " 米\n";
            int flag = 0;
            for (int nodeID : optimalPath.path) {
                if (flag == 0) {
                    Node* ntemp = g.getNode(nodeID);
                    std::cout << nodeID << ". " << ntemp->getName();
                    flag = 1;
                } else {
                    Node* ntemp = g.getNode(nodeID);
                    std::cout << " --> " << nodeID << ". " << ntemp->getName();
                }
            }
            std::cout << "\n";
        }
    }
}