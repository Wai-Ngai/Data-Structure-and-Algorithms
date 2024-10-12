/**
 *   最短路径： Bellman Ford算法, 负权回路
 *   Created by wai-ngai on 24-9-12.
 */

#include <vector>
#include <iostream>
#include <climits>

int main(int argc, char const *argv[]) {
    int n, m, p1, p2, val;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid;

    for (int i = 0; i < m; i++) {
        std::cin >> p1 >> p2 >> val;
        grid.push_back({p1, p2, val});  // p1 指向 p2，权值为 val
    }

    int start = 1; 
    int end = n;
    std::vector<int> min_dist(n + 1, INT_MAX);
    min_dist[start] = 0;
    bool flag = false;

    for (int i = 0; i <= n; i++) {   // 这里我们松弛n次，最后一次判断负权回路
        for (auto& side : grid) {
            int from = side[0];
            int to = side[1];
            int val = side[2];

            if (i < n) {
                if (min_dist[from] != INT_MAX && min_dist[to] > min_dist[from] + val) {
                    min_dist[to] = min_dist[from] + val;
                }
            } else {   // 多加一次松弛判断负权回路
                if (min_dist[from]!= INT_MAX && min_dist[to] > min_dist[from] + val) {
                    flag = true;
                }
            }
        }
    }

    if (flag) {
        std::cout << "circle" << std::endl;
    } else if (min_dist[end] == INT_MAX) {
        std::cout << "unconnected" << std::endl;
    } else {
        std::cout << " min distance : " << min_dist[end] << std::endl;
    }


    return 0;
}

