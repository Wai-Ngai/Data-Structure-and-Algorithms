/**
 *   栈 ： 链表实现
 *   Created by wai-ngai on 24-4-10.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int E;
typedef struct ListNode * ListStack;

struct ListNode {
    E element;
    struct ListNode* next;
};


/**
 *  初始化一个栈
 * @param stack
 * @return
 */
bool InitStack(ListStack stack) {
    stack->next = NULL;
    return 1;
}


/**
 *  入栈，由于是链表，所以在链表头部插入元素，链表的头部就是栈顶，注意这里使用了一个虚拟头结点
 * @param stack
 * @param element
 * @return
 */
bool PushStack(ListStack stack, E element) {
    struct ListNode* new_node = malloc(sizeof(struct ListNode));  // 创建新节点
    if (new_node == NULL) return 0;  // 创建失败，返回false

    new_node->next = stack->next;    // 将新节点的下一个节点，设定为头结点的下一个
    new_node->element = element;     // 设置元素
    stack->next = new_node;          // 将头的下一个设置为新节点

    return 1;
}


bool IsEmpty(ListStack stack) {
    return stack->next == NULL; //判断栈是否为空只需要看头结点下一个是否为NULL即可
}


/**
 *  出栈
 * @param stack
 * @return
 */
E PopStack(ListStack stack) {
    struct ListNode * top = stack->next;  // 因为第一个是虚拟头结点，所以这里找到真正的栈顶
    stack->next = stack->next->next;      // 出栈，移除链表的第一个元素
    E elem = top->element;
    free(top);                        // 释放原栈顶元素
    return elem;                          // 返回出栈元素
}


void PrintStack(ListStack stack) {
    printf("栈顶 | ");
    stack = stack->next;
    while (stack) {
        printf("%d ", stack->element);
        stack = stack->next;
    }
    printf("\n");
}


int main() {
    struct ListNode stack;
    InitStack(&stack);

    for (int i = 1; i < 10; ++i) {
        PushStack(&stack, i*10);
    }
    printf("插入元素成功！ \n");
    PrintStack(&stack);

    printf("正在出栈！ \n");
    printf("栈顶 | ");
    while(!IsEmpty(&stack)) {
        printf("%d ", PopStack(&stack));
    }
}