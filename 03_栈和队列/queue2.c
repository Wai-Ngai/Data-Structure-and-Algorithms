/**
 *   队列 ： 链表实现
 *   Created by wai-ngai on 24-4-10.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int E;
typedef struct ListNode *Node;
typedef struct Queue *ListQueue;

// 定义链表节点
struct ListNode {
    E element;
    struct ListNode *next;
};

// 定义队列
// 因为要存储首尾两个指针，所以这里封装一个新的结构体吧
struct Queue {
    Node front; // 存放指向头节点的指针，也就是虚拟头节点，用于入队操作
    Node rear;  // 指向尾节点的指针，用于入队操作
};


/**
 *  初始化，把头结点先创建出来
 * @param queue
 * @return
 */
bool InitQueue(ListQueue queue) {
    // 创建一个虚拟头结点
    Node dummy_node = malloc(sizeof(struct ListNode));
    if (dummy_node == NULL) return 0;

    dummy_node->next = NULL;
    queue->front = queue->rear = dummy_node; //一开始队列的两个指针都是指向虚拟头节点，表示队列为空
    return 1;
}


/**
 *  入队操作，入队其实直接在后面插入新的节点就行了
 * @param queue
 * @param element
 * @return
 */
bool EnQueue(ListQueue queue, E element) {
    // 创建一个新节点
    Node new_node = malloc(sizeof(struct ListNode));
    if (new_node == NULL) return 0;

    new_node->next = NULL;
    new_node->element = element;

    queue->rear->next = new_node;  // 先将新节点与链表尾部连起来
    queue->rear = new_node;        // 然后移动队尾指针，让队尾指针指向新节点
    return 1;
}


/**
 * 出队操作
 * @param queue
 * @return
 */
E DeQueue(ListQueue queue) {
    E elem = queue->front->next->element;          // 跳过虚拟头节点，取出真正头节点的元素
    Node node = queue->front->next;                // 取出队首节点
    queue->front->next = queue->front->next->next; // 直接让虚拟头结点指向下下个结点

    if (node == queue->rear) {      //如果队尾就是待出队的节点，也就是就剩最后一个节点，那么队尾回到队首位置上
        queue->rear = queue->front;
    }

    free(node);  // 释放出队的节点
    return elem;
}



bool IsEmpty(ListQueue queue) {
    return queue->front == queue->rear;
}


void PrintQueue(ListQueue queue) {
    printf("队首 <<<  ");
    Node node = queue->front->next;  // 跳过虚拟头结点，使用临时指针进行链表遍历
    while (1) {
        printf("%d ", node->element);
        if (node == queue->rear) {  // 当已经打印最后一个元素后，再结束
            break;
        } else {
            node = node->next; // 移动到下一个节点
        }
    }
}


int main() {
    struct Queue queue;
    InitQueue(&queue);

    for (int i = 1; i < 10; ++i) {
        EnQueue(&queue, 10 * i);
    }
    printf("插入元素成功！ \n");
    PrintQueue(&queue);

    printf("\n正在出队！ \n");
    printf("队首 <<< ");
    while (!IsEmpty(&queue)){
        printf("%d ", DeQueue(&queue));
    }
    return 0;
}


