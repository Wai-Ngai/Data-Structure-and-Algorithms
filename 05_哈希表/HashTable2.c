/**
 *   哈希表 ： 数组实现， 解决hash冲突
 *   Created by wai-ngai on 24-4-25.
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

typedef struct Element {
    int key;
}* E;

typedef struct HashTable {
    E * table;
}* HashTable;


int hash(int key) {
    return key % SIZE;
}

bool init(HashTable hash_table) {
    hash_table->table = malloc(sizeof(struct Element) * SIZE);
    if (!hash_table->table) return false;
    for (int i = 0; i < SIZE; ++i) {
        hash_table->table[i] = NULL;
    }
    return true;
}

void insert(HashTable hash_table, E element) {
    int hash_code = hash(element->key);
    int count = 0;
    while (hash_table->table[hash_code]) {   // 如果发现hash冲突，就需要继续寻找一个合适的位置
        hash_code = hash(element->key + ++count);
    }
    hash_table->table[hash_code] = element;
}

bool find(HashTable hash_table, int key) {
    int hash_code = hash(key);
    int count = 0;
    const int start_index = hash_code;   // 记录一下起始位置，转一圈回来就得停

    do {
        if (hash_table->table[hash_code]->key == key) return true;  // 找到
        hash_code = hash(key + ++count);
    } while (start_index != hash_code && hash_table->table[hash_code]);
    return false;
}


E create(int key) {
    E e = malloc(sizeof(struct Element));
    e->key = key;
    return e;
}


int main() {
    struct HashTable hash_table;
    init(&hash_table);
    for (int i = 0; i < 9; ++i) {
        insert(&hash_table, create(i * 9));
    }

    for (int i = 0; i < 9; ++i) {
        printf("%d ", hash_table.table[i]->key);
    }

    return 0;
}