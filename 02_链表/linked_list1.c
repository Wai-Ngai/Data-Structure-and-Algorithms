/**
*  链表实现：单链表
*/

#include <stdio.h>
#include <stdlib.h>

typedef int T;     // 使用别名创建一个通用数据类型T
typedef struct ListNode *Node;

/**
 *   定义一个链表的结构体
 */
struct ListNode {
    T element;                // 保存当前元素
    struct ListNode *next;  // 指向下一个节点的指针
};

/**
 *   链表初始化函数
 * @param list
 * @return
 */
_Bool InitList(Node list) {
    list->next = NULL;   // 头节点默认下一个为NULL
}


/**
 *   插入元素
 * @param list     要插入的链表
 * @param element  要插入的元素
 * @param index    要插入的位置
 * @return         是否插入成功
 */
_Bool InsertElement(Node list, T element, int index) {
    // 判断要插入的index是否越界
    if (index < 1) return 0;
    while (--index) {               // 从头开始向后寻找到index位置
        list = list->next;
        if (list == NULL) return 0;  // 判断找到的节点是否存在，除非要插入的是最后一个位置，该位置非法？
    }

    // 创建新的节点，插入进原list中
    Node new_node = (Node) malloc(sizeof(struct ListNode));
    if (new_node == NULL) return 0;  // 申请内存失败，直接返回
    new_node->element = element;     // 将元素保存至新的节点
    new_node->next = list->next;     // 将新节点指向原本位置上的这个节点
    list->next = new_node;           // 将前节点指向新节点
    return 1;
}


/**
 *  删除元素：根据位序
 * @param list   要删除的链表
 * @param index  链表中的元素位置
 * @return       是否删除成功
 */
_Bool DeleteList(Node list, int index) {
    if (index < 1) return 0;
    while (--index) {
        list = list->next;
        if (list == NULL) return 0;
    }
    if (list->next == NULL) return 0;  //注意删除的范围，如果前驱结点的下一个已经是NULL了，那么也说明超过了范围

    Node tmp = list->next;          // 先取出待删除的节点
    list->next = list->next->next;  // 直接让前驱节点指向下下个节点
    free(tmp);                  // 释放掉待删除节点的内存

    return 1;
}


/**
 *   根据位序查找元素
 * @param list
 * @param index
 * @return
 */
T *GetList(Node list, int index) {
    if (index < 1) return NULL;
    do {
        list = list->next;              // 因为不算头结点，所以使用do-while语句
        if (list == NULL) return NULL;
    } while (--index);                  // 到达index就结束
    return &list->element;
}


/**
 *   在链表中查询目标值，返回该目标值的位序
 * @param list
 * @param target
 * @return
 */
int FindElement(Node list, T target) {
    list = list->next;    // 先走到第一个节点
    int i = 1;
    while (list) {
        if (list->element == target) return 1;  // 如果找到，就返回i
        list = list->next;                      // 如果没有找到，向后移动一个节点，继续找
        i++;
    }
    return -1;  // 如果找到最后都没有找到，就返回-1
}


/**
 *   计算链表的长度
 * @param list
 * @return
 */
int SizeList(Node list) {
    int i = 0;
    while (list->next) {    //如果下一个为NULL那就停止
        list = list->next;
        i++;
    }
    return i;
}

void PrintList(Node list) {
    while (list->next) {
        list = list->next;
        printf("%d ", list->element);  // 因为这里设计的是头结点不存放数据，所以从第二个节点开始打印数据
    }
}


int main() {
    struct ListNode list;
    InitList(&list);

    // 插入节点
    for (int i = 1; i < 4; ++i) {
        _Bool result = InsertElement(&list, 10 * i, i);
        if (!result) {
            printf("插入元素%d失败！\n", i);
        }
    }
    printf("插入元素为：\n");
    PrintList(&list);

    // 删除元素
    _Bool result2 = DeleteList(&list, 1);
    if (!result2) {
        printf("\n 删除元素失败 \n");
    }
    printf("\n删除元素成功：\n");
    PrintList(&list);

    // 计算链表的长度
    int len = SizeList(&list);
    printf("\n链表的长度为： %d \n", len);

    // 根据位序查询元素
    T *element = GetList(&list, 2);
    printf("2号位置的元素是： %d \n", *element);

    // 查找元素
    int index = FindElement(&list, 20);
    if (index != -1) {
        printf("该元素的位置是： %d \n", index);
    } else {
        printf(" 该元素不存在！\n");
    }


    return 0;
}