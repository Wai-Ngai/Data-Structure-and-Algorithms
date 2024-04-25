/**
 *   大顶堆 : 数组实现
 *   Created by wai-ngai on 24-4-25.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int E;
typedef struct MaxHeap * Heap;

struct MaxHeap {
    E * arr;
    int size;
    int capacity;
};


bool InitHeap(Heap heap) {
    heap->size = 0;
    heap->capacity = 10;
    heap->arr = malloc(sizeof(E) * heap->capacity);
    return heap->arr != NULL;
}


/**
 *  插入元素，注意这里数组的0位置不存放元素
 * @param heap
 * @param element
 * @return
 */
bool InsertHeap(Heap heap, E element) {
    if (heap->size == heap->capacity) return 0; // 这里还需要写扩容

    int index = ++heap->size;     // 先计算出要插入的位置，注意要先自增，因为是从1开始的。该元素放在末尾
    while (index > 1 && element > heap->arr[index/2]) {  //然后开始向上堆化，直到符合规则为止，比较末尾元素与父节点元素大小
        heap->arr[index] = heap->arr[index/2]; // 要插入的元素大于父节点元素，交换位置
        index /= 2;
    }
    heap->arr[index] = element; // 在相应的位置插入元素
    return true;
}


/**
 *  删除元素，删除操作实际上就是出队的操作
 * @param heap
 * @return
 */
E DeleteHeap(Heap heap) {
    E max = heap->arr[1];
    E e = heap->arr[heap->size--];

    int index = 1;
    while (index*2 <= heap->size) {  //跟上面一样，开找，只不过是从上往下找
        int child = index * 2;  //先找到左孩子
        //看看右孩子和左孩子哪个大，先选一个大的出来
        if (child < heap->size && heap->arr[child] < heap->arr[child + 1]) child += 1;

        if (e > heap->arr[child]) break;   //如果子结点都不大于新结点，那么说明就是这个位置，结束就行了
        else heap->arr[index] = heap->arr[child]; //否则直接堆化，换上去
        index = child; //最后更新一下index到下面去
    }
    heap->arr[index] = e;  //找到合适位置后，放进去就行了
    return max;
}


void PrintHeap(Heap heap){
    for (int i = 1; i <= heap->size; ++i)
        printf("%d ", heap->arr[i]);
}


int main() {
    struct MaxHeap heap;
    InitHeap(&heap);

    InsertHeap(&heap,5);
    InsertHeap(&heap,2);
    InsertHeap(&heap,3);
    InsertHeap(&heap,7);
    InsertHeap(&heap,6);
    PrintHeap(&heap);


    for (int i = 0; i < 5; ++i) {
        printf("%d ", DeleteHeap(&heap));
    }


    return 0;
}