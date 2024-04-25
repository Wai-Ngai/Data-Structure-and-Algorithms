/**
 *   优先级队列 ： 链表实现
 *   Created by wai-ngai on 24-4-25.
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
 *  优先级队列的入队操作：优先级高的数据可以插队
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

    Node pre = queue->front;
    while (pre->next && pre->next->element > element) {  //我们从头结点开始往后挨个看，直到找到第一个小于当前值的结点，或者到头为止
        pre = pre->next;
    }
    if (pre == queue->rear) {          // 如果说找到的位置已经是最后了，那么直接插入就行，这里跟之前是一样的
        queue->rear->next = new_node;  // 先将新节点与链表尾部连起来
        queue->rear = new_node;        // 然后移动队尾指针，让队尾指针指向新节点
    } else {
        new_node->next = pre->next;   // 否则开启VIP模式，直接插队
        pre->next = new_node;
    }
    return 1;
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


int main(){
    struct Queue queue;
    InitQueue(&queue);

    EnQueue(&queue, 9);
    EnQueue(&queue, 4);
    EnQueue(&queue, 7);
    EnQueue(&queue, 3);
    EnQueue(&queue, 13);

    PrintQueue(&queue);
}


