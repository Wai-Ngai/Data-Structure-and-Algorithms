/**
 *   水流问题： 深度优先搜索，dfs
 *   Created by wai-ngai on 24-7-08.
 */
#include <iostream>
#include <vector>

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(const std::vector<std::vector<int>>& graph, std::vector<std::vector<bool>>& visited, int x, int y) {
    if (visited[x][y]) return;
    
    visited[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];
        if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph[0].size()) continue;
        if (graph[x][y] > graph[next_x][next_y]) continue;
        dfs(graph, visited, next_x, next_y);
    }
}

int main(){
    int m, n;
    std::cout << "输入岛屿的行和列数量：" << std::endl;
    std::cin >> m >> n;

    std::vector<std::vector<int>> graph(m, std::vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> graph[i][j];
        }
    }

    std::vector<std::vector<bool>> first_bound(m, std::vector<bool>(n, false));
    std::vector<std::vector<bool>> second_bound(m, std::vector<bool>(n, false));

    for (int i = 0; i < m; i ++) {
        dfs(graph, first_bound, i, 0);
        dfs(graph, second_bound, i, n-1);
    }

    for (int j = 0; j < n; j++) {
        dfs(graph, first_bound, 0, j);
        dfs(graph, second_bound, m-1, j);
    }    

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (first_bound[i][j] && second_bound[i][j]) {
                std::cout << i << j << std::endl;
            }
        }
    } 

    return 0;
};