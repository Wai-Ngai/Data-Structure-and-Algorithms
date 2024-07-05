/**
 *   图 ： 使用邻接表存储
 *   Created by wai-ngai on 24-7-04.
 */




#include <iostream>
#include <vector>
#include <list>

std::vector<std::vector<int>> result;
std::vector<int> path;

void dfs(std::vector<std::list<int>> graph, int x, int n) {
    if (x == n)
    {
        result.push_back(path);
        return;
    }
    for (int i : graph[x]) { // 找到 x指向的节点
        path.push_back(i);   // 遍历到的节点加入到路径中来
        dfs(graph, i, n);
        path.pop_back();
    }

}

int main(int argc, char const *argv[])
{
    int n, m, s, t;

    std::cin >> n >> m;
    std::vector<std::list<int>> graph(n+1);  // 节点编号从1到n，所以申请 n+1 这么大的数组
    while (m--)
    {
        std::cin >> s >> t;
        graph[s].push_back(t);  // 使用邻接表 ，表示 s -> t 是相连的
    }
    
    path.push_back(1); // 无论什么路径已经是从0节点出发
    dfs(graph, 1, n);

    if (result.size() == 0) std::cout << -1 << std::endl;
    for (const std::vector<int> &pa : result) {
        for (int i = 0; i < pa.size() - 1; i++) {
            std::cout << pa[i] << " ";
        }
        std::cout << pa[pa.size() - 1]  << std::endl;
    }

    return 0;
}
