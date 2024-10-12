/**
 *   最大岛屿面积： 广度优先搜索，bfs
 *   Created by wai-ngai on 24-7-05.
 */


#include <vector>
#include <queue>
#include <iostream>

int count;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void bfs(const std::vector<std::vector<int>> &graph, std::vector<std::vector<bool>> &visited, int x, int y) {
    std::queue<std::pair<int, int>> que;
    que.push({x, y});
    count++;
    visited[x][y] = true;

    while (!que.empty()) {
        int curent_x = que.front().first;
        int curent_y = que.front().second;
        que.pop();

        for (int i = 0; i < 4; i++) {
            int next_x = curent_x + dir[i][0];
            int next_y = curent_y + dir[i][1];

            if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph[0].size()) continue;           
            if (graph[next_x][next_y] == 1 && !visited[next_x][next_y]) {
                count++;
                visited[next_x][ next_y] = true;
                que.push({next_x, next_y});
            }
        }
    }
}


int main() {
    int m, n;
    std::cout << "输入岛屿的行和列数量：" << std::endl;
    std::cin >> m >> n;

    std::vector<std::vector<int>> graph(m,std::vector<int>(n, 0));
    std::cout << "请输入岛屿位置：" << std::endl;
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
                bfs(graph, visited, i, j);
                result = std::max(result, count);
            }
        }
    }

    std::cout << "bfs搜索，最大岛屿的面积为：" << result << std::endl;

    return 0;
} 