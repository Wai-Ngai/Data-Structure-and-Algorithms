/**
 *   最短路问题: A* 算法
 *   Created by wai-ngai on 24-9-13.
 */

#include <iostream>
#include <string.h>
#include <queue>

int b1, b2;
int moves[1001][1001];

// 骑士移动的方向：日字移动
int dir[8][2] = {-2, -1,
                 -2, 1,
                 -1, 2,
                  1, 2,
                  2, 1,
                  2, -1,
                  1, -2,
                 -1, -2};

// F = G + H
// G = 从起点到该节点路径消耗
// H = 该节点到终点的预估消耗
struct Knight {
    int x, y;
    int g, h, f;

    bool operator < (const Knight & k) const { // 重载运算符， 从小到大排序
        return k.f < f;
    }
};

std::priority_queue<Knight> que;

int Heuristic(const Knight& k) {
    return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2);  // 欧拉距离，统一不开根号，这样可以提高精度
}

void Astar(const Knight& k) {
    Knight cur, next;
    que.push(k);                               // 放入起点

    while (!que.empty()) {
        cur = que.top(); que.pop();            // 取出f最小的节点

        if (cur.x == b1 && cur.y == b2) break; // 到达目标节点

        for (int i = 0; i < 8; i++) {
            next.x = cur.x + dir[i][0];        // 按照规则，朝8个方向移动，计算下一个点
            next.y = cur.y + dir[i][1];

            if (next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000) continue;  // 超过边界

            if (!moves[next.x][next.y]) {       // 该节点没有被访问过
                moves[next.x][next.y] = moves[cur.x][cur.y] + 1;   // 移动的步数

                next.g = cur.g + 5;                 // 统一不开根号，这样可以提高精度，马走日，所以移动的距离是5，1 * 1 + 2 * 2 = 5
                next.h = Heuristic(next);           // 当前位置到终点的距离
                next.f = next.g + next.h;
                que.push(next);
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    // 第一行包含一个整数 n，表示测试用例的数量。
    int n, a1, a2;
    std::cin >> n;

    while (n--) {
        // 接下来的 n 行，每行包含四个整数 a1, a2, b1, b2，分别表示骑士的起始位置 (a1, a2) 和目标位置 (b1, b2)。
        std::cin >> a1 >> a2 >> b1 >> b2;
        memset(moves, 0, sizeof(moves));  // 初始化或重置一块内存

        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        start.f = start.g + start.h;

        Astar(start);

        while (!que.empty()) que.pop(); // 队列清空

        // 输出共 n 行，每行输出一个整数，表示骑士从起点到目标点的最短路径长度。
        std::cout<< std::endl;
        std::cout << moves[b1][b2];
    }

    return 0;
}
