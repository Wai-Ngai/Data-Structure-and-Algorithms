/**
 *   DFS ： 邻接表实现图存储，深度优先搜索
 *   Created by wai-ngai on 24-10-12.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MaxVertex 6                     // 创建时，我们可以指定图中初始有多少个结点

typedef char E;                         // 顶点存放的数据类型

typedef struct Node {                   // 结点和头结点分开定义，普通结点记录邻接顶点信息
    int next_vertex;                    // 普通节点的值
    struct Node* next;
} * Node;

struct HeadNode {                       // 头结点记录元素
    E element;                          // 头节点的值
    struct Node* next;
};

typedef struct AdjacencyGraph {
    int vertex_count;
    int edge_count;
    struct HeadNode vertex[MaxVertex];   // 邻接表，只保存头节点
} * Graph;


Graph Creat() {
    Graph graph = malloc(sizeof(struct AdjacencyGraph));
    graph->vertex_count = 0;
    graph->edge_count = 0;
    return graph;
}

void AddVertex(Graph graph, E element) {
    if (graph->vertex_count >= MaxVertex) return;
    graph->vertex[graph->vertex_count].element = element;
    graph->vertex[graph->vertex_count].next = NULL;
    graph->vertex_count++;
}


void AddEdge(Graph graph, int from, int to) {         // 添加几号顶点到几号顶点的边
    // 创建新节点
    Node new_node = malloc(sizeof(struct Node));
    new_node->next = NULL;
    new_node->next_vertex = to;

    // 找到当前节点的下一个节点
    Node node = graph->vertex[from].next;
    if (!node) {
        graph->vertex[from].next = new_node;          // 当前节点没有连接其他节点
    } else {                                          // 否则说明当前顶点已经连接了至少一个其他顶点了，有可能会出现已经连接过的情况，所以说要特别处理一下
        do {
            if (node->next_vertex == to) {            // 要插入的节点已经存在，直接返回
                free(new_node);
                return; 
            } 

            if (node->next) {                         // 否则继续向后遍历
                node = node->next;
            } else {
                break;                                // 如果没有下一个了，那就找到最后一个结点了，直接结束
            }
        } while(1);
        node->next = new_node;
    }
    graph->edge_count++;                              // 边数计数+1
}

void PrintGraph(Graph graph){
    for (int i = 0; i < graph->vertex_count; ++i) {
        printf("%d | %c", i, graph->vertex[i].element);
        Node node = graph->vertex[i].next;
        while (node) {
            printf(" -> %d", node->next_vertex);
            node = node->next;
        }
        putchar('\n');
    }
}


/**
 * @brief 深度优先搜索算法
 * 
 * @param Graph 
 * @param start     起始顶点下标
 * @param target    目标顶点下标
 * @param visited   已经访问过的顶点数组
 * @return true 
 * @return false 
 */
bool dfs(Graph Graph, int start, int target, int * visited) {
    visited[start] = 1;                                             // 标记访问过
    printf("%c -> ", Graph->vertex[start].element);                 // 打印当前顶点值

    if (start == target) return true;                               // 如果当前顶点就是要找的顶点，直接返回

    Node node = Graph->vertex[start].next;                          // 遍历当前顶点所有的分支
    while (node) {
        if (!visited[node->next_vertex]) {                          // 如果已经到过（有可能是走其他分支到过，或是回头路）那就不继续了
            if (dfs(Graph, node->next_vertex, target, visited)) {   // 没到过就继续往下走，这里将start设定为对于分支的下一个顶点，按照同样的方式去寻找
                return true;                                        // 如果查找成功，直接返回1，不用再看其他分支了
            } 
        }
        node = node->next;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    Graph graph = Creat();      // 初始化图

    // 构建一个有向图
    for (int c = 'A'; c <= 'F'; ++c) {
        AddVertex(graph, (char)c);
    }
    AddEdge(graph, 0, 1);   // A -> B
    AddEdge(graph, 1, 2);   // B -> C
    AddEdge(graph, 1, 3);   // B -> D
    AddEdge(graph, 1, 4);   // D -> E
    AddEdge(graph, 4, 5);   // E -> F

    PrintGraph(graph);

    // 定义访问数组，用于标记该顶点是否访问过
    int visited[graph->vertex_count];
    for (int i = 0; i < graph->vertex_count; ++i) {
        visited[i] = 0;
    }

    dfs(graph, 0, 3, visited);  // 查找D节点 

    return 0;
}
