/**
 *   哈希表 ： 数组实现
 *   Created by wai-ngai on 24-4-25.
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 9


typedef struct Element {  //这里用一个Element将值包装一下
    int key;
}* E;

typedef struct HashTable {  //这里把数组封装为一个哈希表
    E * table;
}* HashTable;


int hash(int key) {  //哈希函数
    return key % SIZE;
}

void init(HashTable hash_table) { //初始化函数
    hash_table->table = malloc(sizeof(struct Element) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        hash_table->table[i] = NULL;
    }
}

void insert(HashTable hash_table, E element) {
    int hash_code = hash(element->key);    //首先计算元素的哈希值
    hash_table->table[hash_code] = element;
}

bool find(HashTable hash_table, int key) {
    int hash_code = hash(key);                              // 首先计算元素的哈希值
    if (hash_table->table[hash_code] == NULL) return false; // 如果为NULL那就说明没有
    return hash_table->table[hash_code]->key == key;             // 如果有，直接看是不是就完事
}

E create(int key) {
    E e = malloc(sizeof(struct Element));
    e->key = key;
    return e;
}


int main(){
    struct HashTable hashTable;
    init(&hashTable);
    insert(&hashTable, create(10));
    insert(&hashTable, create(7));
    insert(&hashTable, create(13));
    insert(&hashTable, create(29));

    printf("%d\n", find(&hashTable, 1));
    printf("%d\n", find(&hashTable, 13));


    return 0;
}