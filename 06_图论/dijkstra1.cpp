/**
 *   最短路径： dijstra算法, 朴素版：原始思路
 *   Created by wai-ngai on 24-9-09.
 */


#include <iostream>
#include <vector>
#include <climits>



int main(int argc, char const *argv[]) {
    int m , n, p1, p2, val;

    // 一共n个公共汽车站， m条公路
    std::cin >> n >> m;

    // 接下来的m行，每行3个整数S、E 和 V，代表了从 S 车站可以单向直达 E 车站，并且需要花费 V 单位的时间。
    std::vector<std::vector<int>> grid(n+1, std::vector<int>(n+1, INT_MAX));
    for (int i = 0; i < m; i++) {
        std::cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;                  // 使用邻接矩阵存储图
    }

    int start = 1;
    int end = n;

    std::vector<int> min_dist(n+1, INT_MAX);  // 从起点到每个节点的最短距离
    std::vector<int> path(n+1, -1);           // 记录路径
    std::vector<bool> visited(n+1, false);    // 记录该节点是否被访问过
    min_dist[start] = 0;                      // 起点到自身的距离为0

    // 遍历所以节点（车站）
    for (int i = 1; i <= n; i++) {
        int min_val = INT_MAX;
        int cur_node = 1;

        // 1.选距离起点最近且未被访问过的节点
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && min_dist[j] < min_val) {
                min_val = min_dist[j];
                cur_node = j;
            }
        }

        // 2. 标记访问过的节点
        visited[cur_node] = true;

        // 3. 更新非访问节点到起点的距离
        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && grid[cur_node][j] != INT_MAX  && min_dist[cur_node] + grid[cur_node][j] < min_dist[j]) {
                min_dist[j] = min_dist[cur_node] + grid[cur_node][j];
                path[j] = cur_node;  // 记录边
            }
        }

        // 打印日志
        std::cout << "select: " << cur_node << std::endl;
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

    // 输出最短路径
    for (int i = 1; i <= n; ++i) {
        std::cout << path[i] << " -> " << i << std::endl;
    }
    return 0;
}

