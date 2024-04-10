/**
 *   队列： 顺序表实现
 *   Created by wai-ngai on 24-4-10.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int E;
typedef struct Queue* ArrayQueue;

struct Queue {
    E* array;
    int capacity;   // 数组容量
    int front;      // 队首指针
    int rear;       // 队尾指针
};

bool InitQueue(ArrayQueue queue) {
    queue->array = malloc(sizeof(E) * 10);
    if (queue->array == NULL) return 0;

    queue->capacity = 10;
    queue->front = queue->rear = 0;  //默认情况下队首和队尾都指向0的位置
    return 1;
}

bool EnQueue(ArrayQueue queue, E element) {
    int pos = (queue->rear + 1) % queue->capacity;  //队尾先向前移动一位，注意取余计算才能实现循环，也就是容量，刚满以后，将尾指针移动到数组0位置
    if (pos == queue->front) {   //先判断队列是否已满，如果队尾下一个就是队首，那么说明数组已满，注意这里数组总是有一个位置没有装元素，不然不好判断是否装满
        printf("插入元素失败！队列已满 \n");
        return 0;
    }
    queue->rear = pos;
    queue->array[pos] = element;  //在新的位置插入元素
    return 1;
}


bool IsEmpty(ArrayQueue queue) {
    return queue->front == queue->rear;
}

E DeQuque(ArrayQueue queue) {
    if (IsEmpty(queue)) return -1;

    queue->front = (queue->front + 1) % queue->capacity; //先将队首指针后移1位，因为这里队首指针指向一个空位置
    return queue->array[queue->front]; // 出队
}


void PrintQueue(ArrayQueue queue) {
    printf("<<< ");

    int i = queue->front;   //遍历队列需要从队首开始
    do {
        i = (i + 1) % queue->capacity;          // 先向后循环移动
        printf("%d ", queue->array[i]);  // 然后打印当前位置上的元素
    } while (i != queue->rear);                 // 当到达队尾时，结束

    printf(" <<< \n");
}


int main() {
    struct Queue queue;
    InitQueue(&queue);

    for (int i = 1; i < 11; ++i) {
        bool res = EnQueue(&queue, 10 * i);
        printf("%d \n", res);
    }
    printf("插入元素成功！ \n");
    PrintQueue(&queue);

    printf("正在出队！ \n");
    printf("队首 <<< ");
    while (!IsEmpty(&queue)) {
        printf("%d ", DeQuque(&queue));
    }
}