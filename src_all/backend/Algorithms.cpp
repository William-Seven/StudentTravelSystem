#include "Algorithms.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <limits>
#include <map>
#include <random>
#include <stack>
#include <utility>

#define DNF std::numeric_limits<double>::max()  // 定义一个无限大的值用于表示无法到达
#define INF std::numeric_limits<int>::max()     // 定义一个无限大的值用于表示无法到达

// 模拟退火算法相关参数
const double START_TEMPERATURE = 50000.0;
const double END_TEMPERATURE = 1.0;
const double COOLING_RATE = 0.998;

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
Algorithms::PathResult Algorithms::findFastestPath(Graph& graph, int startNodeID, int endNodeID, int mode) {
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
        int transportmode = static_cast<Edge::type>(mode);
        for (const auto& edge : graph.getNode(u)->edges) {
            if (edge->transportMode == transportmode) {
                int v = edge->getTo()->id;
                double alt = times[u] + edge->getLength() / (edge->getSpeed() * (1 - edge->getCongestion()));
                if (alt < times[v]) {
                    times[v] = alt;
                    predecessors[v] = u;
                }
            } else {
                // 如果不是当前交通方式的边，则跳过
                continue;
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

void permutations(Algorithms::PathResult& result, Graph& graph, int startNodeID, std::vector<int> arr, int l, int r) {
    if (l == r) {
        // 基础条件：如果左右指针相遇
        double tempLength = 0;
        std::vector<int> tempPath;
        for (int i = 0; i < arr.size(); i++) {
            if (i == 0) {
                Algorithms::PathResult temp = Algorithms::findShortestPath(graph, startNodeID, arr[i]);
                tempLength += temp.length;
                for (int j = 0; j < temp.path.size(); j++) {
                    tempPath.push_back(temp.path[j]);
                }
            } else {
                Algorithms::PathResult temp = Algorithms::findShortestPath(graph, arr[i - 1], arr[i]);
                tempLength += temp.length;
                for (int j = 1; j < temp.path.size(); j++) {
                    tempPath.push_back(temp.path[j]);
                }
            }
        }
        Algorithms::PathResult temp = Algorithms::findShortestPath(graph, arr.back(), startNodeID);
        tempLength += temp.length;
        for (int j = 1; j < temp.path.size(); j++) {
            tempPath.push_back(temp.path[j]);
        }

        if (tempLength < result.length) {
            result.length = tempLength;
            result.path = tempPath;
        }
    } else {
        // 对于数组中的每个元素，将其与左侧元素交换，然后递归打印右侧子数组的排列
        for (int i = l; i <= r; i++) {
            // 交换 arr[l] 和 arr[i]
            std::swap(arr[l], arr[i]);
            // 递归打印右侧子数组的排列
            permutations(result, graph, startNodeID, arr, l + 1, r);
            // 回溯：交换回来，恢复原样
            std::swap(arr[l], arr[i]);
        }
    }
}

// 暴力算法，全排列
Algorithms::PathResult Algorithms::findBruteForcePath(Graph& graph, int startNodeID, std::vector<int>& targets) {
    PathResult result;
    int size = targets.size();
    result.length = INF;
    permutations(result, graph, startNodeID, targets, 0, size - 1);

    return result;
}

// 模拟退火算法
Algorithms::PathResult Algorithms::simulatedAnnealing(Graph& completeGraph, int startNodeID, std::vector<int>& nodes) {
    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // 初始化路径和路径长度
    Algorithms::PathResult currentResult;
    currentResult.path = nodes;
    currentResult.path.insert(currentResult.path.begin(), startNodeID);
    currentResult.path.push_back(startNodeID);

    for (int i = 0; i < currentResult.path.size() - 1; ++i)
        for (auto edg : completeGraph.getNode(currentResult.path[i])->edges)
            if (edg->getTo()->id == currentResult.path[i + 1]) {
                currentResult.length += edg->getLength();
                break;
            }

    Algorithms::PathResult bestResult = currentResult;

    double temperature = START_TEMPERATURE;

    // 退火过程
    while (temperature > END_TEMPERATURE) {
        std::vector<int> newPath = currentResult.path;

        // 扰动
        int i = 1 + rand() % (newPath.size() - 2);  // 避免改变起点和终点
        int j = 1 + rand() % (newPath.size() - 2);
        std::swap(newPath[i], newPath[j]);

        Algorithms::PathResult newResult;
        newResult.path = newPath;
        for (int i = 0; i < newResult.path.size() - 1; ++i)
            for (auto edgs : completeGraph.getNode(newResult.path[i])->edges)
                if (edgs->getTo()->id == newResult.path[i + 1]) {
                    newResult.length += edgs->getLength();
                    break;
                }

        double delta = newResult.length - currentResult.length;
        if (delta < 0 || dis(gen) < exp(-delta / temperature))
            currentResult = newResult;

        if (currentResult.length < bestResult.length)
            bestResult = currentResult;

        temperature *= COOLING_RATE;
    }

    return bestResult;
}

// 构造完全图并使用模拟退火算法
Algorithms::PathResult Algorithms::findOptimalPath(Graph& graph, int startNodeID, std::vector<int>& targets) {
    // 构造完全图
    int n = targets.size();
    Graph completeGraph(n + 1);                             // 包含起点和所有目标点
    std::map<std::pair<int, int>, std::vector<int>> paths;  // 存放完全图路径

    // 完全图节点添加
    Node* t = graph.getNode(startNodeID);
    completeGraph.addNode(startNodeID, t->getType(), t->getName(), t->getDescription());
    for (int i = 0; i < n; i++) {
        Node* temp = graph.getNode(targets[i]);
        completeGraph.addNode(targets[i], temp->getType(), temp->getName(), temp->getDescription());
    }

    // 完全图路径添加
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Algorithms::PathResult result = Algorithms::findShortestPath(graph, targets[i], targets[j]);
            completeGraph.addEdge(targets[i], targets[j], result.length, 0, 0, Edge::type::WALK);
            std::pair<int, int> key1(targets[i], targets[j]);
            std::pair<int, int> key2(targets[j], targets[i]);
            paths.insert(std::make_pair(key1, result.path));
            std::reverse(result.path.begin(), result.path.end());
            paths.insert(std::make_pair(key2, result.path));
        }
        Algorithms::PathResult resultStart = Algorithms::findShortestPath(graph, startNodeID, targets[i]);
        completeGraph.addEdge(startNodeID, targets[i], resultStart.length, 0, 0, Edge::type::WALK);
        std::pair<int, int> key1(startNodeID, targets[i]);
        std::pair<int, int> key2(targets[i], startNodeID);
        paths.insert(std::make_pair(key1, resultStart.path));
        std::reverse(resultStart.path.begin(), resultStart.path.end());
        paths.insert(std::make_pair(key2, resultStart.path));
    }

    // 模拟退火求解
    Algorithms::PathResult ret = simulatedAnnealing(completeGraph, startNodeID, targets);

    // 根据途径点的顺序，添加中间的node
    std::vector<int> finalpath;
    for (int i = 0; i < ret.path.size() - 1; i++) {
        std::pair<int, int> key(ret.path[i], ret.path[i + 1]);
        auto it = paths.find(key);
        finalpath.insert(finalpath.end(), it->second.begin(), it->second.end() - 1);
    }
    finalpath.push_back(ret.path.back());
    ret.path = finalpath;

    return ret;
}