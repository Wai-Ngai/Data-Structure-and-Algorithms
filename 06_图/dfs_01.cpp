/**
 *   3.所有可达路径：dfs 使用邻接矩阵存储
 *   Created by wai-ngai on 24-7-04.
 */


#include <vector>
#include <iostream>

std::vector<std::vector<int>> result;  // 搜集符合条件的路径
std::vector<int> path;                 // 从1到终点的一条路径

void dfs(const std::vector<std::vector<int>> &graph, int x, int n) {
    if (x == n) {
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (graph[x][i] == 1) {
            path.push_back(i);
            dfs(graph, i, n);
            path.pop_back();
        }
    }
    
    
}

int main(int argc, char const *argv[]) {
    // 图有n个节点，m条边
    int n, m, s, t;
    std::cin >> n >> m;

    // n从1开始，所以申请n+1 * n+1的矩阵
    std::vector<std::vector<int>> graph(n+1, std::vector<int>(n+1, 0));

    // 每一条边开始记录
    while (m--) {
        std::cin >> s >> t; // 表示节点s 和 t 链接
        graph[s][t] = 1;
    }
    
    // 从1节点开始
    path.push_back(1); 
    dfs(graph, 1, n);

    // 输出结果
    for (const auto &pa : result) {
        for (int i = 0; i < pa.size()-1; i++) {
            std::cout << pa[i] << " ";
        }
        std::cout << pa[pa.size()-1] << std::endl;
    }

    return 0;
}
