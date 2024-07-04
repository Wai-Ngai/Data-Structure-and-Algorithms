/**
 *   岛屿数量：深度优先搜索，dfs
 *   Created by wai-ngai on 24-7-04.
 */

#include <iostream>
#include <vector>


// 四个方向
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(const std::vector<std::vector<int>>& graph, std::vector<std::vector<bool>>& visited, int x, int y) {
    if (visited[x][y] || graph[x][y] == 0)  {
        return;            // 终止条件：访问过的节点 或者 遇到海水
    }
    visited[x][y] = true;   // 标记访问过
    for (int i = 0; i < 4; ++i) {
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];

        if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph[0].size()) continue; // 越界了，直接跳过
        dfs(graph, visited, next_x, next_y);
    }
}

int main() {
    int m, n;
    std::cout << "输入岛屿的行和列数量：" << std::endl;
    std::cin >> m >> n;

    std::vector<std::vector<int>> graph(m, std::vector<int>(n, 0));
    std::cout << "请输入岛屿位置：" << std::endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> graph[i][j];
        }
    }

    int result = 0;
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j] && graph[i][j]) {
                result++;                           // 遇到没访问过的陆地，+1
                dfs(graph, visited, i, j);  // 将与其链接的陆地都标记上 true
            }
        }
    }
    std::cout << "岛屿数量是：" << result << std::endl;

    return 0;
}