/**
 *   最短路径： Bellman Ford算法
 *   Created by wai-ngai on 24-9-11.
 */


#include <iostream>
#include <vector>
#include <climits>

int main(int argc, char const *argv[]) {
    int n, m, p1, p2, val;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid;

    // input edges
    for (int i = 0; i < m; ++i) {
        std::cin >> p1 >> p2 >> val;
        grid.push_back({p1, p2, val});  // p1 指向 p2，权值为 val
    }
    
    int start = 1;
    int end = n;
    std::vector<int> min_dist(n + 1, INT_MAX);
    min_dist[start] = 0;

    for (int i = 0; i < n+1; ++i) { // 对所有边松弛n-1次
        for (auto& side : grid) {
            int from = side[0];   // 边的出发点
            int to = side[1];     // 边的到达点
            int price = side[2];  // 边的权值

            // 松弛操作
            if (min_dist[from] != INT_MAX && min_dist[to] > min_dist[from] + price) {
                min_dist[to] = min_dist[from] + price;
            }
        }
        std::cout << "对所有边松弛 " << i << "次" << std::endl;
        for (int k = 1; k <= n; k++) {
            std::cout << min_dist[k] << " ";
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
