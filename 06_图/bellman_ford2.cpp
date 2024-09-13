/**
 *   最短路径： Bellman Ford算法, 基于队列优化
 *   Created by wai-ngai on 24-9-11.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>

// 邻接表
struct Edge {
    int to;   // 链接的节点
    int val;  // 边的权重

    Edge(int t, int v) : to(t), val(v) {};
};

int main(int argc, char const *argv[]) {
    int n, m, p1, p2, val;
    std::cin >> n >> m;

    std::vector<std::list<Edge>> grid(n + 1);
    std::vector<bool> is_in_queue(n + 1);

    // 用邻接表保存图
    std::cout << "input the graph : " << std::endl;
    for (int i = 0; i < m; ++i) {
        std::cin >> p1 >> p2 >> val;
        grid[p1].push_back(Edge(p2, val));    // p1 指向 p2，权值为 val
    }

    int start = 1;
    int end = n;
    std::vector<int> min_dist(n + 1, INT_MAX);
    min_dist[start] = 0;
    
    std::queue<int> que;
    que.push(start);

    while (!que.empty()) {
        int node = que.front();
        que.pop();
        is_in_queue[node] = false;

        for (auto edge : grid[node]) {
            int from = node;
            int to = edge.to;
            int price = edge.val;

            if (min_dist[to] > min_dist[from] + price) {   // 开始松弛
                min_dist[to] = min_dist[from] + price;
                if (!is_in_queue[to]) {                    // 已经在队列里的元素不用重复添加
                    que.push(to);
                    is_in_queue[to] = true;
                }
            }
        }
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
