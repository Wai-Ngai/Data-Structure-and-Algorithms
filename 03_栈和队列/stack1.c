/**
 *   栈 ： 顺序表实现
 *   Created by wai-ngai on 24-4-10.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


// 定义一个栈的节点
typedef  int E;
typedef struct Stack* ArrayStack;

struct Stack {
    E* array;     // 一个指向类型为 E 的数组的指针，用于存储栈中的元素
    int capacity;
    int top;      //这里使用top来表示当前的栈顶位置，存的是栈顶元素的下标
};


/**
 *  初始化一个栈
 * @param stack
 * @return
 */
bool InitStack(ArrayStack stack) {
    stack->array = malloc(sizeof(E) * 10);  // 为数组申请10*E大小的空间
    if (stack->array == NULL) return 0;

    stack->capacity = 10;  // 容量还是10
    stack->top = -1;       //由于栈内没有元素，那么栈顶默认就为-1
    return 1;
}


/**
 *  入栈，因为是数组实现的栈，所以数组的第一个元素就是栈底
 * @param stack
 * @param element
 * @return
 */
bool PushStack(ArrayStack stack, E element) {
    //栈顶+1(top从0开始)如果等于容量的话，那么说明已经塞满了
    if (stack->top + 1 == stack->capacity) {
        int new_capacity = stack->capacity + (stack->capacity >> 1);      // 新的容量大小为原来的1.5倍
        E* new_array = realloc(stack, new_capacity * sizeof(E));
        if (new_array == NULL) return 0;

        stack->array = new_array;
        stack->capacity = new_capacity;
    }

    stack->array[++stack->top] = element;  // 直接在栈顶添加元素，注意这里先移动top到一个新的位置，再添加元素
    return 1;
}


/**
 *  判断栈是否为空
 * @param stack
 * @return
 */
bool IsEmpty(ArrayStack stack) {
    return stack->top == -1;
}


/**
 * 出栈
 * @param stack
 * @return
 */
E PopStack(ArrayStack stack) {
    if (IsEmpty(stack)) {
        printf("栈是空的，请先添加元素！");
        return -1;
    }
    return stack->array[stack->top--]; //直接返回栈顶元素，注意多加一个自减操作
}


void PrintStack(ArrayStack stack) {
    printf("栈底 | ");
    for (int i = 0; i < stack->top + 1; ++i) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main () {
    struct Stack stack;
    InitStack(&stack);

    for (int i = 1; i < 10; ++i) {
        PushStack(&stack, i * 10);
    }
    printf("插入元素成功！ \n");
    PrintStack(&stack);

    printf("正在出栈！ \n");
    while (!IsEmpty(&stack)) {
        printf("%d ",PopStack(&stack));
    }
}