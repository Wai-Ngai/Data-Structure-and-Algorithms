/**
 *   3.所有可达路径：dfs 使用邻接表存储
 *   Created by wai-ngai on 24-7-04.
 */

#include <vector>
#include <iostream>
#include <list>

std::vector<std::vector<int>> result;
std::vector<int> path;

void dfs(const std::vector<std::list<int>>& graph, int x, int n) {
    if (x == n) {
        result.push_back(path);
        return;
    }
    for (int i : graph[x]) {  // 注意使用邻接表，这里不一样
        path.push_back(i);
        dfs(graph, i, n);
        path.pop_back();
    }
}



int main(int argc, const char** argv) {
    int n, m, s, t;
    std::cin >> n >> m;

    std::vector<std::list<int>> graph(n+1);

    while (m--) {
        std::cin >> s >> t;
        graph[s].push_back(t);
    }

    path.push_back(1);
    dfs(graph, 1, n);

    std::cout << " result "<< std::endl;

    for (const auto& pa : result) {
        for (int i = 0; i < pa.size()-1; i++) {
            std::cout << pa[i] << " ";
        }
        std::cout << pa[pa.size()-1] << std::endl;
    }

    return 0;
}
