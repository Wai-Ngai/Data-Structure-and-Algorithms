/**
 *   最短路问题: A* 算法
 *   Created by wai-ngai on 24-9-13.
 */

#include <iostream>
#include <string.h>
#include <queue>

int b1, b2;
int moves[1001][1001];
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

    bool operator < (const Knight & k) const {// 重载运算符， 从小到大排序
        return k.f < f;
    }
};

std::priority_queue<Knight> que;

int Heuristic(const Knight& k) {
    return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2);  // 欧拉距离
}

void astar(const Knight& k) {
    Knight cur, next;
    que.push(k);

    while (!que.empty()) {
        cur = que.top(); que.pop();
        if (cur.x == b1 && cur.y == b2) break;

        for (int i = 0; i < 8; i++) {
            next.x = cur.x + dir[i][0];
            next.y = cur.y + dir[i][1];

            if (next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000) continue;

            if (!moves[next.x][next.y]) {
                moves[next.x][next.y] = moves[cur.x][cur.y] + 1;

                next.g = cur.g + 5;
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                que.push(next);
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    int n, a1, a2;
    std::cin >> n;

    while (n--) {
        std::cin >> a1 >> a2 >> b1 >> b2;
        memset(moves, 0, sizeof(moves));  // 初始化或重置一块内存

        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        start.f = start.g + start.h;

        astar(start);

        while (!que.empty()) que.pop(); // 队列清空

        std::cout<< std::endl;
        std::cout << moves[b1][b2];
    }

    return 0;
}
