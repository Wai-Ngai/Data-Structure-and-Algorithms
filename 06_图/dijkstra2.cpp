/**
 *   最短路径： dijstra算法, 堆优化版
 *   Created by wai-ngai on 24-9-10.
 */

#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <iostream>

// 带权重的边
struct Edge{
    int to;   // 邻接节点
    int val;  // 权重

    Edge(int t, int v) : to(t), val(v) {};
};

// 小顶堆
class MyCompare {
public:
    bool operator() (const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};


int main(int argc, const char** argv) {
    // 一共n个公共汽车站， m条公路
    int m, n, p1, p2, val;
    std::cin >> n >> m;

    std::vector<std::list<Edge>> grid(n + 1);

    for (int i = 0; i < m; i++) {
        std::cin >> p1 >> p2 >> val;
        grid[p1].push_back(Edge(p2, val));  // p2指向p1，权值为val
    }

    int start = 1;
    int end = n;

    std::vector<int> min_dist(n + 1, INT_MAX);  // 存储从起点到每个节点的最短距离
    std::vector<bool> visited(n + 1, false);    // 记录该节点是否被访问过
    min_dist[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, MyCompare> pq;  // 优先级队列， 存放pair<节点， 起点到该节点的权重>
    pq.push(std::pair<int, int>(start, 0));     // 初始化队列，起点到起点的距离为0

    while (!pq.empty()) {
        // 1. 选起点到哪个节点的距离最近
        // <节点， 源点到该节点的距离>
        std::pair<int, int> cur = pq.top();
        pq.pop();
        if (visited[cur.first]) continue;

        // 2. 标记该节点
        visited[cur.first] = true;

        // 3. 更新与当前节点连接，且未访问过的节点到起点的距离
        for (Edge  edge : grid[cur.first]) { // 遍历当前节点指向的边
            // cur指向的节点edge.to，这条边的权值为 edge.val
            if (!visited[edge.to] && min_dist[cur.first] + edge.val < min_dist[edge.to]) {
                min_dist[edge.to] = min_dist[cur.first] + edge.val;
                pq.push({edge.to, min_dist[edge.to]});
            }
        }
        // 打印日志
        std::cout << "select: " << cur.first << std::endl;
        for (int k = 1; k <= n; ++k) {
            std::cout << k << " : " << min_dist[k] << " ";
        }
        std::cout << std::endl;
    }

    if (min_dist[end] == INT_MAX) {
        std::cout << "无法到达终点" << std::endl;
        std::cout << -1 << std::endl;
    } else {
        std::cout << "到达终点的最短距离为： " << std::endl;
        std::cout << min_dist[end] << std::endl;
    }

    return 0;
}