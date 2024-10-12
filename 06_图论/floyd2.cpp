/**
 *   多源最短路问题: Floyd算法，优化空间
 *   Created by wai-ngai on 24-9-13.
 */

#include <vector>
#include <iostream>

int main(int argc, char const *argv[]) {
    int n, m, p1, p2, val;
    std::cin >> n >> m;

    std::vector<std::vector<int>> grid(n + 1, std::vector<int> (n + 1, 10005));
    for (int i = 0; i < m; i++) {
        std::cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;
        grid[p2][p1] = val;
    }
    
    // Floyd 
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                grid[i][j] = std::min(grid[i][j], grid[i][k] + grid[k][j]);
            }
        }
    }

    // 输出结果
    int z, start, end;
    std::cin >> z;
    while (z--) {
        std::cin >> start >> end;
        if (grid[start][end] == 10005) {
            std::cout << "-1" << std::endl;
        } else {
            std::cout <<"从" << start << "到" << end <<"的最短路径： ";
            std::cout << grid[start][end] << std::endl;
        }
    }

    return 0;
}
