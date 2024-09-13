/**
 *   岛屿数量： 广度优先搜索，bfs
 *   Created by wai-ngai on 24-7-04.
 */

#include <vector>
#include <iostream>
#include <queue>

int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};

void bfs(const std::vector<std::vector<int>>& graph, std::vector<std::vector<bool>>& visited, int x, int y) {
    std::queue<std::pair<int, int>> que;
    que.push({x,y});
    visited[x][y] = true;

    while (!que.empty()) {
        int cur_x = que.front().first;
        int cur_y = que.front().second;
        que.pop();

        for (int i = 0; i < 4; i ++) {
            int next_x = cur_x + dir[i][0]; 
            int next_y = cur_y + dir[i][1]; 
            if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph[0].size()) continue;
            if (graph[next_x][next_y] == 1 && !visited[next_x][next_y]) {
                que.push({next_x, next_y});
                visited[next_x][next_y] = true;
            }
        }
    }
    
}


int main () {
    int m, n;
    std::cout << "输入岛屿的行和列数量：" << std::endl;
    std::cin >> m >> n;

    std::vector<std::vector<int>> graph(m, std::vector<int>(n, 0));

    std::cout << "请输入岛屿位置：" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
        }
    }

    int result = 0;
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && !visited[i][j]) {
                result++;
                bfs(graph, visited, i, j);
            }
        }
    }

    std::cout << "岛屿数量：" << result << std::endl;

    return 0;
}