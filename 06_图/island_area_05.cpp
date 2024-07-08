/**
 *   沉没孤岛： 将中间的岛屿置零，广度优先搜索，bfs
 *   Created by wai-ngai on 24-7-08.
 */
#include <iostream>
#include <vector>

int count = 0; // 统计符合题目要求的陆地空格数量
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(std::vector<std::vector<int>> &graph, int x, int y) {
    if (graph[x][y] == 0 || graph[x][y] == 2) {
        return;
    }
    graph[x][y] =2;
    for (int i = 0; i < 4; ++i) {
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];
        if (next_x < 0 || next_x > graph.size()-1 || next_y < 0 || next_y > graph[0].size()-1) continue;
        dfs(graph, next_x, next_y);
    }
}

int main()  {
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

    // form left/right edge to mid
    for (int i = 0; i < m; ++i) {
        if (graph[i][0] == 1) dfs(graph, i, 0);
        if (graph[i][n-1] == 1) dfs(graph, i, n-1);
    }
    // form top/ bottom to mid
    for (int j = 0; j < n; ++j) {
        if (graph[0][j] == 1) dfs(graph, 0, j);
        if (graph[m-1][j] == 1) dfs(graph, m-1, j);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == 1) graph[i][j] = 0;
            if (graph[i][j] == 2) graph[i][j] = 1;
        }
    }

    std::cout << "沉没孤岛后岛屿是：" << std::endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << graph[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
