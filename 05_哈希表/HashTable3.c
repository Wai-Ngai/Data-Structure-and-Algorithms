/**
 *   哈希表 ： 链表实现， 解决hash冲突
 *   Created by wai-ngai on 24-4-25.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

typedef struct ListNode {  //结点定义
    int key;
    struct ListNode *next;
} *Node;

typedef struct HashTable {  //哈希表
    struct ListNode *table;  //这个数组专门保存头结点
} *HashTable;


void init(HashTable hash_table) {
    hash_table->table = malloc(sizeof(struct ListNode) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        hash_table->table[i].key = -1;    //将头结点key置为-1，next指向NULL
        hash_table->table[i].next = NULL;
    }
}

int hash(int key) {
    return key % SIZE;
}

/**
 *  创建节点
 * @param key
 * @return
 */
Node creatNode(int key) {
    Node node = malloc(sizeof(struct ListNode));
    node->key = key;
    node->next = NULL;
    return  node;
}

/**
 *  插入元素
 * @param hash_table
 * @param key
 */
void insert(HashTable hash_table, int key) {
    int hash_code = hash(key);
//    Node head = &hash_table->table[hash_code];  // 找到链表的头节点
    Node head = hash_table->table + hash_code;  // 找到链表的头节点
    while (head->next) head = head->next;       // 找到可以插入的位置
    head->next = creatNode(key);
}


/**
 *  查找元素
 * @param hash_talbe
 * @param key
 * @return
 */
bool find(HashTable hash_talbe, int key) {
    int hash_code = hash(key);
    Node head = hash_talbe + hash_code;
    while (head->next && head->key != key) {  //直到最后或是找到为止
        head = head->next;
    }
    return head->key == key;  //直接返回是否找到
}



int main() {
    struct HashTable hash_table;
    init(&hash_table);

    insert(&hash_table, 19);
    insert(&hash_table, 10);
    insert(&hash_table, 20);

    printf("%d \n", find(&hash_table, 19));
    printf("%d \n", find(&hash_table, 10));
    printf("%d \n", find(&hash_table, 21));

    return 0;
}
