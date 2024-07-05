/**
 *   图 ： 使用邻接矩阵存储
 *   Created by wai-ngai on 24-7-04.
 */


#include <iostream>
#include <vector>

std::vector<std::vector<int>> result;  // 收集符合条件的路径
std::vector<int> path;                 // 1节点到终点的路径

void dfs(std::vector<std::vector<int>>& graph, int x, int end) {
    // 当前遍历的节点x 到达节点n 
    if (x == end) {
        result.push_back(path);
        return;
    }
    for (int i = 1; i <= end; i++) {// 遍历节点x链接的所有节点
        if (graph[x][i] == 1) {     // 找到 x链接的节点
            path.push_back(i);      // 遍历到的节点加入到路径中来
            dfs(graph, i, end);     // 进入下一层递归
            path.pop_back(); // 回溯，撤销本节点
        }
    }
    
}

int main(int argc, const char** argv) {
    int n = 0, m = 0, s = 0, t = 0;

    std::cout << "请输入第一个行，第一行包含两个整数 N,M,表示图中拥有 N 个节点,M 条边" << std::endl;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n + 1, std::vector<int>(n + 1, 0)); // 节点编号从1到n，所以申请 n+1 这么大的数组

    std::cout<< "请输入图的链接，两个整数 s 和 t, 表示图中的 s 节点与 t 节点中有一条路径"<< std::endl;
    while (m--) {
        std::cin >> s >> t;
        graph[s][t] = 1;  // 使用邻接矩阵 表示无向图，1 表示 s 与 t 是相连的
    }
    path.push_back(1); // 无论什么路径已经是从0节点出发
    dfs(graph, 1, n);

    // 输出结果
    std::cout << "查找到的路径为："<< std::endl;
    if (result.size() == 0) std::cout << -1 << std::endl;

     for (const auto & elem : result) {
         for (int i = 0; i < elem.size()-1; i++)
         {
             std::cout << elem[i] << " ";
         }
         std::cout << elem[elem.size()-1] << std::endl;
     }

    return 0;
}