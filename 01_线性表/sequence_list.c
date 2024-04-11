/**
*    顺序表：底层使用数组实现
*/

#include <stdio.h>
#include <stdlib.h>

typedef int T;     // 使用别名创建一个通用数据类型T
typedef struct List *ArrayList;

struct List {
    T *array;      // 指向顺序表的底层数组
    int capacity;  // 表示底层数组的容量
    int size;      // 表中元素的数量
};

/**
 *  初始化顺序表
 * @param list 要初始化的表
 * @return     是否初始化成功
 */
_Bool initList(ArrayList list) {
    list->array = (T *) malloc(sizeof(T) * 10);  // 使用malloc函数申请10个int类型大小的空间，供底层数组使用。这里的强制类型转换非必须，因为void*可以隐式转换为任意类型的指针
    if (list->array == NULL) {
        return 0;  // 如果内存空间申请失败，返回0
    }
    list->capacity = 10;
    list->size = 0;
    return 1;
}

/**
 *   插入元素
 * @param list     要插入的表
 * @param element  要插入的元素
 * @param index    要插入的位置， 从1开始
 * @return         是否插入成功
 */
_Bool insertList(ArrayList list, T element, int index) {
    // 判断插入位置是否合法
    if (index < 1 || index > list->size + 1) {
        return 0;
    }
    // 判断是否需要扩容
    if (list->size == list->capacity) {
        int new_capacity = list->capacity + (list->capacity >> 1); // 新的容量大小为原来的1.5倍
        T *new_array = (T *) realloc(list->array, sizeof(T) * new_capacity); // realloc函数调整原空间的大小
        if (new_array == NULL) {  // 判断新申请内存是否成功
            return 0;
        }
        list->array = new_array;
        list->capacity = new_capacity;
    }

    // 将待插入位置的元素往后移动
    for (int i = list->size; i > index - 1; i--) {
        list->array[i] = list->array[i - 1];
    }
    // 插入新的元素
    list->array[index - 1] = element;
    list->size++;
    return 1;
}


/**
 *   删除元素
 * @param list   要删除的列表
 * @param index  要删除的位置
 * @return       是否删除成功
 */
_Bool deleteList(ArrayList list, int index) {
    if (index < 1 || index > list->size + 1) {
        return 0;
    }
    for (int i = index - 1; i < list->size - 1; ++i) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
    return 1;
}


/**
 *   获取列表的长度
 * @param list
 * @return
 */
int sizeList(ArrayList list) {
    return list->size;
}


/**
 *  按照位置获取元素
 * @param list   要查找的列表
 * @param index  要查找的位置
 * @return       该位置上的元素
 */
T *getList(ArrayList list, int index) {
    if (index < 1 || index > list->size) {
        return NULL;
    }
    return &list->array[index - 1];
}


/**
 *  查找元素
 * @param list     要查找的列表
 * @param element  要查找的元素
 * @return         该元素的位置
 */
int findList(ArrayList list, T element) {
    for (int i = 0; i < list->size; ++i) {
        if (list->array[i] == element) {
            return i + 1;
        }
    }
    return -1;
}

void printList(ArrayList list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

int main() {
    struct List list;
    if (initList(&list)) {
        printf("初始列表成功！ \n");

        // 插入元素
        printf("插入元素... \n");
        for (int i = 0; i < 10; ++i) {
            insertList(&list, 10 * i, i);
        }
        printList(&list);
        printf("插入元素成功！ \n");

    } else {
        printf("初始化列表失败，请重新启动程序");
    }

    if (deleteList(&list, 5)) {
        printf("删除元素成功 \n");
        deleteList(&list, 8);
        printList(&list);
        printf("该列表的元素个数为：%d \n", sizeList(&list));
    } else {
        printf("删除元素失败！\n");
    }

    T *a = getList(&list, 7);
    printf("位置8的元素是：%d \n", *a);
    return 0;
}
