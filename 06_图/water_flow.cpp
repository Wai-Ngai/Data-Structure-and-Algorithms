/**
 *   水流问题： 深度优先搜索，dfs
 *   Created by wai-ngai on 24-7-08.
 */
#include <iostream>
#include <vector>

int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void dfs(std::vector<std::vector<int>> &graph,std::vector<std::vector<bool>> &visited, int x, int y) {
    if (visited[x][y]) return;
    visited[x][y] = true;

    for (int i = 0; i < 4; ++i) {
        int next_x = x + dir[i][0];
        int next_y = y + dir[i][1];
        if (next_x < 0 || next_x > graph.size()-1 || next_y < 0 || next_y > graph[0].size()-1) continue;
        if (graph[x][y] > graph[next_x][next_y]) continue; // 注意：这里是从低向高遍历
        dfs(graph, visited, next_x, next_y);
    }
}


int main(){
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

    std::vector<std::vector<bool>> firstBoundary(m, std::vector<bool>(n, false));   // 标记从第一组边界上的节点出发，可以遍历的节点
    std::vector<std::vector<bool>> secondBoundary(m, std::vector<bool>(n, false));  // 标记从第一组边界上的节点出发，可以遍历的节点

    // form left / right to mid
    // 从最上和最下行的节点出发，向高处遍历
    for (int i = 0; i < m; ++i) {
        dfs(graph, firstBoundary, i, 0);
        dfs(graph, secondBoundary, i, n-1);
    }

    // form top / bottom to mid
    // 从最左和最右列的节点出发，向高处遍历
    for (int j = 0; j < m; ++j) {
        dfs(graph, firstBoundary, 0, j);
        dfs(graph, secondBoundary, m-1, j);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            // 如果这个节点，从第一组边界和第二组边界出发都遍历过，就是结果
            if (firstBoundary[i][j] && secondBoundary[i][j]) {
                std::cout << i << "  " << j << std::endl;
            }
        }
    }

    return 0;
};