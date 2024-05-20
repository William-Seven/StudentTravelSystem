#include "Algorithms.h"
#include <algorithm>
#include <limits>
#include <stack>

#define DNF std::numeric_limits<double>::max()  // 定义一个无限大的值用于表示无法到达
#define INF std::numeric_limits<int>::max()     // 定义一个无限大的值用于表示无法到达

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

// TSP途径点最短路径
/*
Algorithms::PathResult Algorithms::findTspPath(std::vector<std::vector<double>>& dist, int startNodeID, std::vector<int>& targets) {
    int n = dist.size();          // 所有节点总数
    int t_size = targets.size();  // 途径点数量
    PathResult result;
    // 计算所有目标节点都被访问的掩码值
    int VISITED_ALL = (1 << t_size) - 1;

    // 初始化一个二维 DP 表格，每个位置的值默认设置为无穷大
    std::vector<std::vector<double>> dp(1 << t_size, std::vector<double>(t_size, DNF));
    // 初始化路径追踪表格
    std::vector<std::vector<int>> path(1 << t_size, std::vector<int>(t_size, -1));

    // 初始化 DP 表，从起始点开始
    dp[1 << 0][0] = 0;
    for (int i = 0; i <= VISITED_ALL; i++)
        dp[1 << i][i] = dist[targets[i]][startNodeID];

    // 遍历所有可能的目标节点子集组合
    for (int mask = 0; mask <= VISITED_ALL; mask++) {
        for (int i = 0; i < t_size; ++i) {
            // 检查目标节点 i 是否在当前子集中,如果包含（不执行continue）
            if (!(mask & (1 << i)))
                continue;

            // 遍历所有可能的上一个目标节点
            for (int j = 0; j < t_size; ++j) {
                // 排除 i 自己或 j 不在当前子集内的情况
                if (i == j || !(mask & (1 << j)))
                    continue;

                // 计算移除当前节点 i 后的子集组合
                int prev_mask = mask ^ (1 << i);
                double new_cost = dp[prev_mask][j] + dist[targets[j]][targets[i]];

                // 更新 DP 表格中的值，选择更小的路径成本
                if (new_cost <= dp[mask][i]) {
                    dp[mask][i] = new_cost;
                    path[mask][i] = j;
                }
                // dp[mask][i] = std::min(dp[mask][i], dp[prev_mask][j] + dist[targets[j]][targets[i]]);
            }
        }
    }

    // 计算返回起始点的最小成本+路径
    double min_cost = dp[VISITED_ALL][0];
    int last_node = 0;
    std::vector<int> order;
    int mask = VISITED_ALL;
    order.push_back(targets[last_node]);
    while (path[mask][last_node] != -1) {
        last_node = path[mask][last_node];
        mask ^= (1 << last_node);
        order.push_back(targets[last_node]);
    }
    std::reverse(order.begin(), order.end());

    result.length = min_cost;
    std::cout << min_cost << std::endl;
    result.path = order;

    return result;
}
*/
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

// 暴力
Algorithms::PathResult Algorithms::findBruteForcePath(Graph& graph, int startNodeID, std::vector<int>& targets) {
    PathResult result;
    int size = targets.size();
    result.length = INF;
    permutations(result, graph, startNodeID, targets, 0, size - 1);

    return result;
}