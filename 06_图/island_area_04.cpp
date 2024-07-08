/**
 *   孤岛屿面积： 广度优先搜索，bfs
 *   Created by wai-ngai on 24-7-08.
 */


#include <iostream>
#include <vector>
#include <queue>
#include <list>

int count = 0; // 统计符合题目要求的陆地空格数量
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};

void bfs(std::vector<std::vector<int>> &graph, int x, int y) {
    std::cout << "in bfs" << std::endl;

    std::queue<std::pair<int,int>> que;
    que.push({x,y});
    graph[x][y] = 0; // 只要加入队列，立刻标记
    count++;

    while (!que.empty()) {
        int cur_x = que.front().first;
        int cur_y = que.front().second;
        que.pop();
        for (int i = 0; i < 4; ++i) {
            int next_x = cur_x + dir[i][0];
            int next_y = cur_y + dir[i][1];
            if (next_x < 0 || next_x > graph.size()-1 || next_y < 0 || next_y > graph[0].size()-1) continue;
            if (graph[next_x][next_y] == 0) continue;
            que.push({next_x, next_y});
            graph[next_x][next_y] = 0;
            count++;
        }
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
    std::cout << "从左、右向中间消除岛屿：" << std::endl;
    for (int i = 0; i < m; ++i) {
        if (graph[i][0] == 1) bfs(graph, i, 0);
        if (graph[i][n-1] == 1) bfs(graph, i, n-1);
    }
    // form top/ bottom to mid
    std::cout << "从上、下向中间消除岛屿：" << std::endl;
    for (int j = 0; j < n; ++j) {
        if (graph[0][j] == 1) bfs(graph, 0, j);
        if (graph[m-1][j] == 1) bfs(graph, m-1, j);
    }

    // calculate lonely island count
    std::cout << "计算孤岛的数量" << std::endl;
    count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] == 1) bfs(graph, i, j);
        }
    }

    std::cout << "孤岛的面积是：" << count << std::endl;
    return 0;
}