/**
 *   孤岛屿面积： 深度优先搜索，dfs
 *   Created by wai-ngai on 24-7-08.
 */


#include <iostream>
#include <vector>

int count = 0; // 统计符合题目要求的陆地空格数量
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(std::vector<std::vector<int>>& graph, int x, int y) {
//    std::cout << "in dfs" << std::endl;
    if (graph[x][y] == 0) {
        return;
    }

    graph[x][y] = 0;
    count++;
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

    // 从左、右向中间
    for (int i = 0; i < m; ++i) {
        if (graph[i][0] == 1) dfs(graph, i, 0);
        if (graph[i][n-1] == 1) dfs(graph, i, n-1);
    }
    // 从上、下向中间
    for (int i = 0; i < n; ++i) {
        if (graph[0][i] == 1) dfs(graph, 0, i);
        if (graph[m-1][i] == 1) dfs(graph, m-1, i);
    }

    count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == 1) dfs(graph, i, j);
        }
    }

    std::cout << "孤岛的面积是：" << count << std::endl;
    return 0;
}