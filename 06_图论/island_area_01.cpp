/**
 *   最大岛屿面积： 深度优先搜索，dfs
 *   Created by wai-ngai on 24-7-04.
 */


#include <vector>
#include <iostream>

int count;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0 -1};

void dfs(const std::vector<std::vector<int>> &graph, std::vector<std::vector<bool>> &visited, int x, int y) {
    if (graph[x][y] == 0 || visited[x][y]) {
        return;
    }
    visited[x][y] = true;
    count++;

    for (int i = 0; i < 4; i++) {
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];
        if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph[0].size()) continue;
        dfs(graph, visited, next_x, next_y);
    }
}


int main(int argc, char const *argv[]) {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> graph(m, std::vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
        }
    }

    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    int result = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && !visited[i][j]) {
                count = 0;
                dfs(graph, visited, i, j);
                result = std::max(result, count);
            }
        }
    }

    std::cout << "dfs搜索，最大岛屿的面积为：" << result << std::endl;

    return 0;
}
