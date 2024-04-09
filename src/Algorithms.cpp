#include "Algorithms.h"
#include <limits>
#include <stack>

// 辅助函数，用于找到尚未访问的具有最小距离（时间）的节点
int findMinDistanceNode(HashMap<int, double, HashFunc>& distance, HashMap<int, bool, HashFunc>& visited, int size) {
    double minDistance = std::numeric_limits<double>::max();
    int minNode = -1;
    for (int i = 0; i < size; i++) {
        double nodeDistance = *(distance.find(i));
        if (!*(visited.find(i)) && nodeDistance < minDistance) {
            minDistance = nodeDistance;
            minNode = i;
        }
    }
    return minNode;
}

// 寻找最短路径算法
Algorithms::PathResult Algorithms::findShortestPath(Graph& graph, int startNodeID, int endNodeID) {
    int numNodes = graph.size;  // 图中节点总数
    // 初始化距离、前驱节点和访问标记的哈希表
    HashMap<int, double, HashFunc> distances(numNodes);
    HashMap<int, int, HashFunc> predecessors(numNodes);
    HashMap<int, bool, HashFunc> visited(numNodes);
    PathResult result;

    // 初始化
    for (int i = 0; i < numNodes; ++i) {
        distances.insert(i, std::numeric_limits<double>::max());
        predecessors.insert(i, -1);
        visited.insert(i, false);
    }
    distances[startNodeID] = 0;

    for (int i = 0; i < numNodes; ++i) {
        int u = findMinDistanceNode(distances, visited, numNodes);
        if (u == -1)
            break;  // 所有节点都已访问
        if (u == endNodeID)
            break;  // 找到最短路径

        visited[u] = true;

        for (const auto& edge : graph.getNode(u)->edges) {
            int v = edge->getTo()->id;
            double alt = distances[u] + edge->distance;
            if (alt < distances[v]) {
                distances[v] = alt;
                predecessors[v] = u;
            }
        }
    }

    // 重建从endNodeId到startNodeId的路径
    std::stack<int> pathStack;
    for (int at = endNodeID; at != -1; at = predecessors[at])
        pathStack.push(at);

    if (!pathStack.empty() && pathStack.top() == startNodeID) {  // 如果路径存在
        while (!pathStack.empty()) {
            result.path.push_back(pathStack.top());
            pathStack.pop();
        }
        result.length = distances[endNodeID];
    }

    return result;
}

// 寻找最快路径算法
Algorithms::PathResult Algorithms::findFastestPath(Graph& graph, int startNodeID, int endNodeID) {
    int numNodes = graph.size;  // 图中节点总数
    // 初始化时间、前驱节点和访问标记的哈希表
    HashMap<int, double, HashFunc> times(numNodes);
    HashMap<int, int, HashFunc> predecessors(numNodes);
    HashMap<int, bool, HashFunc> visited(numNodes);
    PathResult result;

    for (int i = 0; i < numNodes; i++) {
        times.insert(i, std::numeric_limits<double>::max());  // 初始化时间为无穷大
        predecessors.insert(i, -1);                           // 初始化前驱节点为-1
        visited.insert(i, false);                             // 初始化节点为未访问
    }
    times[startNodeID] = 0;  // 起点时间设为0

    // 使用Dijkstra算法计算最快路径
    for (int i = 0; i < numNodes; i++) {
        int u = findMinDistanceNode(times, visited, numNodes);  // 找到未访问的最小时间节点
        if (u == -1)                                            // 无可访问的节点（都已访问）
            break;
        if (u == endNodeID)  // 如果找到终点，则跳出循环
            break;

        visited[u] = true;  // 标记该节点为已访问

        // 遍历所有出边，更新时间和前驱节点
        for (const auto& edge : graph.getNode(u)->edges) {
            int v = edge->getTo()->id;
            double alt = times[u] + edge->getLength() / (edge->getSpeed() * (1 - edge->getCongestion()));
            if (alt < times[v]) {
                times[v] = alt;
                predecessors[v] = u;
            }
        }
    }

    // 从终点开始。使用前驱节点重建路径
    std::stack<int> pathStack;
    for (int at = endNodeID; at != -1; at = predecessors[at])
        pathStack.push(at);  // 将节点压入栈

    // 如果路径存在（即栈顶元素为起点），则构建PathResult对象
    if (!pathStack.empty() && pathStack.top() == startNodeID) {
        while (!pathStack.empty()) {
            result.path.push_back(pathStack.top());  // 将栈顶元素添加到路径中
            pathStack.pop();                         // 弹出栈顶元素
        }
        result.time = times[endNodeID];  // 设置路径的总时间
    }

    return result;  // 返回路径结果对象
}