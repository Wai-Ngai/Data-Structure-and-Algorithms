/**
 *   多源最短路问题: Floyd算法
 *   Created by wai-ngai on 24-9-13.
 */


#include <vector>
#include <iostream>


int main(int argc, char const *argv[]) {
    int n, m, p1, p2, val;
    std::cin >> n >> m;

    // 使用三维数组保存图
    std::vector<std::vector<std::vector<int>>> grid(n + 1, std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1, 10005)));
    for (int i= 0; i < m; i++) {
        std::cin >> p1 >> p2 >> val;
        grid[p1][p2][0] = val;
        grid[p2][p1][0] = val;    // 双向图
    }
    
    // Floyd 算法 ： 动态规划
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                grid[i][j][k] = std::min(grid[i][j][k-1], grid[i][k][k-1] + grid[k][j][k-1]);
            }
        }
    }

    // 输出结果
    int z, start, end;
    std::cin >> z;
    while (z--) {
        std::cin >> start >> end;
        if (grid[start][end][n] == 10005) {
            std::cout << "-1" << std::endl;
        } else {
            std::cout <<"从" << start << "到" << end <<"的最短路径： ";
            std::cout << grid[start][end][n] << std::endl;
        }
    }

    return 0;
}
