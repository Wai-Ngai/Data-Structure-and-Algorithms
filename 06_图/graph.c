/**
 *   有向图 ： 邻接矩阵实现
 *   Created by wai-ngai on 24-10-11.
 */


#include <stdlib.h>
#include <stdio.h>


#define MaxVertex 5                     // 创建时，我们可以指定图中初始有多少个结点

typedef char E;                         // 顶点存放的数据类型

typedef struct MatrixGraph {            
    int vertex_count;                   // 顶点的数量
    int edge_count;                     // 边的数量
    int matrix[MaxVertex][MaxVertex];   // 邻接矩阵
    E data[MaxVertex];                  // 各个顶点对应数据
} * Graph;

Graph Creat() {
    Graph graph = malloc(sizeof(struct MatrixGraph)); // 顶点和边数肯定一开始是0
    graph->vertex_count = 0;
    graph->edge_count = 0;

    for (int i = 0; i < MaxVertex; i++) {
        for (int j = 0; j < MaxVertex; j++) {
            graph->matrix[i][j] = 0;                  // 记得把矩阵每个位置都置为0
        }
    }
    return graph;
}

void AddVertex(Graph graph, E element) {
    if (graph->vertex_count >= MaxVertex) return;     // 满了
    graph->data[graph->vertex_count++] = element;     // 添加新元素
}

void AddEdge(Graph graph, int from, int to) {         // 添加几号顶点到几号顶点的边
    if (graph->matrix[from][to] == 0) {
        graph->matrix[from][to] = 1;                  // 注意如果是无向图的话，需要[a][b]和[b][a]都置为1
        graph->edge_count++;
    }
}

void PrintGraph(Graph graph){
    for (int i = -1; i < graph->vertex_count; ++i) {
        for (int j = -1; j < graph->vertex_count; ++j) {
            if(j == -1)
                printf("%c", 'A' + i);
            else if(i == -1)
                printf("%3c", 'A' + j);
            else
                printf("%3d", graph->matrix[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[]) {
    Graph graph = Creat();      // 初始化图

    // 构建一个有向图
    for (int c = 'A'; c <= 'D'; ++c) {
        AddVertex(graph, (char)c);
    }
    AddEdge(graph, 0, 1);
    AddEdge(graph, 0, 1);   //A -> B
    AddEdge(graph, 1, 2);   //B -> C
    AddEdge(graph, 2, 3);   //C -> D
    AddEdge(graph, 3, 0);   //D -> A
    AddEdge(graph, 2, 0);   //C -> A

    PrintGraph(graph);

    return 0;
}
