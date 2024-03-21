/**
*  链表实现：双向链表
*/

#include <stdio.h>
#include <stdlib.h>


typedef int T;
typedef struct ListNode *Node;

struct ListNode {
    T element;
    struct ListNode *next;  // 指向下一个节点的指针
    struct ListNode *prev;  // 指向上一个节点的指针
};


void InitList(Node list) {
    list->next = list->prev = NULL;
}


/**
 *   双向链表插入元素
 * @param list
 * @param target
 * @param index
 * @return
 */
_Bool InsertList(Node list, T target, int index) {
    if (index < 1) return 0;  // 跟单链表一样，还是先找到对应的位置
    while (--index) {
        list = list->next;
        if (list == NULL) return 0;
    }
    Node new_node = (Node) malloc(sizeof(struct ListNode));  // 创建新的节点
    if (new_node == NULL) return 0;

    new_node->element = target;
    // 处理后继节点
    if (list->next) { // 后继节点存在
        list->next->prev = new_node;
        new_node->next = list->next;
    } else {
        new_node->next = NULL;  // 后继节点不存在
    }
    // 处理前驱节点
    list->next = new_node;
    new_node->prev = list;

    return 1;
}


/**
 *  根据位序删除节点
 * @param list
 * @param index
 * @return
 */
_Bool DeleteList(Node list, int index) {
    //跟单链表一样，还是先找到对应的位置
    if (index < 1) return 0;
    while (--index) {
        list = list->next;
        if (list == NULL) return 0;
    }
    if (list->next == 0) return 0;

    //先拿到待删除结点
    Node temp = list->next;
    if (list->next->next) { //这里有两种情况待删除结点存在后继结点或是不存在
        list->next->next->prev = list;
        list->next = list->next->next;
    } else {
        list->next = NULL; //相当于删的是最后一个结点，所以直接后继为NULL就完事
    }
    free(temp); //最后释放已删除结点的内存

    return 1;
}

/**
 *   输出链表
 * @param list
 */
void PrintList(Node list) {
    Node node = list;   //先来正向遍历一次
    do {
        node = node->next;
        printf("%d -> ", node->element);
    } while (node->next != NULL);

    printf("\n");   //再来反向遍历一次
    do {
        printf("%d -> ", node->element);
        node = node->prev;
    } while (node->prev != NULL);
}


int main() {
    struct ListNode list;
    InitList(&list);

    // 插入元素
    for (int i = 1; i < 11; ++i) {
        InsertList(&list, 10 * i, i);
    }
    PrintList(&list);

    // 删除元素
    _Bool res = DeleteList(&list, 5);
    if (res) {
        printf("\n删除元素成功！\n");
    } else {
        printf("\n删除元素失败\n");
    }
    PrintList(&list);
}

