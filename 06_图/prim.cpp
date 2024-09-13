/**
 *   最小生成树： prim算法
 *   Created by wai-ngai on 24-9-06.
 */


#include <iostream>
#include <vector>



int main(int argc, char const *argv[]) {
    int v, e;
    int x, y, k;

    std::cin >> v >> e;
    std::vector<std::vector<int>> grid(v+1, std::vector<int>(v+1, 10001));
    while (e--) {
        std::cin >> x >> y >> k;
        grid[x][y] = k;
        grid[y][x] = k;
    }

    std::vector<int> min_dist(v+1, 10001);
    std::vector<bool> is_in_tree(v+1, false);
    std::vector<int> parent(v+1, -1);

    for (int i = 1; i < v; i++) {
        int cur = -1;
        int min_val = INT16_MAX;
        for (int j = 1; j <= v; j++) {
            if (!is_in_tree[j] && min_dist[j] < min_val) {
                min_val = min_dist[j];
                cur = j;
            }
        }

        is_in_tree[cur] = true;

        for (int j = 0; j <= v; j++) {
            if (!is_in_tree[j] && grid[cur][j] < min_dist[j]) {
                min_dist[j] = grid[cur][j];
                parent[j] = cur;
            }
        }
    }
    int result = 0;
    for (int i = 2; i <= v; i++) {
        result += min_dist[i];
    }

    std::cout << result << std::endl;

    // 输出 最小生成树边的链接情况
    for (int i = 1; i <= v; i++) {
        std::cout << i << "->" << parent[i] << std::endl;
    }   

    return 0;
}
