/**
 *   最大岛屿面积： 广度优先搜索，dbfs
 *   Created by wai-ngai on 24-7-05.
 */


#include <iostream>
#include <vector>
#include <queue>
#include <list>

int island_area;
int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
void bfs(const std::vector<std::vector<int>>& graph,  std::vector<std::vector<bool>>& visited, int x, int y) {
    if (visited[x][y] || graph[x][y] == 0) return;
    std::queue<std::pair<int,int>> que;
    que.push({x,y}); // 加入队列就意味节点是陆地可到达的点
    visited[x][y] = true;
    island_area++;

    while (!que.empty()) {
        int cur_x = que.front().first;
        int cur_y = que.front().second;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int next_x = cur_x + dir[i][0];
            int next_y = cur_y + dir[i][1];
            if (next_x < 0 || next_x >= graph.size() || next_y < 0 || next_y >= graph.size()) continue; // 越界
            if (!visited[next_x][next_y] && graph[next_x][next_y] == 1) { // 节点没有被访问过且是陆地
                que.push({next_x,next_y});
                visited[next_x][next_y] = true;
                island_area++;
            }
        }
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
            if (!visited[i][j] && graph[i][j] == 1) {
//                std::cout<<"island area  "<< island_area<<std::endl;
                island_area = 0;                       // 因为bfs处理当前节点，所以遇到陆地计数为0，进vfs之后在开始从1计数
                bfs(graph, visited, i, j);
                result = std::max(result, island_area);
            }
        }
    }

    std::cout << "bfs搜索，最大岛屿的面积为：" << result << std::endl;

    return 0;
}