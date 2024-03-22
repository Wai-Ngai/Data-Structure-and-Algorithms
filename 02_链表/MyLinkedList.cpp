//
// Created by wai-ngai on 24-3-22.
//
#include <iostream>

using namespace std;

// 定义链表节点结构体
struct LinkedNode {
    int val;
    LinkedNode* next;
    LinkedNode(int value) : val(value), next(nullptr) {};
};

class MyLinkedList {
public:
    MyLinkedList() {
        dummy_head_ = new LinkedNode(0);  // 定义一个虚拟头结点
        size_ = 0;
    }

    // 获取链表中第 index 个节点的值。如果索引无效，则返回-1。
    int get(int index) {
        if (index < 0 || index > size_ - 1) return -1;

        LinkedNode * cur = dummy_head_->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }

    // 在链表的第一个元素之前添加一个值为 val 的节点。
    void addAtHead(int val) {
        LinkedNode * new_node = new LinkedNode(val);  // 创建一个新的节点
        new_node->next = dummy_head_->next;
        dummy_head_->next = new_node;
        size_++;
    }

    // 将值为 val 的节点追加到链表的最后一个元素。
    void addAtTail(int val) {
        auto new_node = new LinkedNode(val);  // 创建一个新的节点

        LinkedNode * cur = dummy_head_;
        while (cur->next != nullptr) {   // 一直往后找到最后一个节点
            cur = cur->next;
        }
        cur->next = new_node;
        size_++;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    // 如果index小于0，则在头部插入节点
    void addAtIndex(int index, int val) {
        if (index > size_) return;
        if (index < 0) index = 0;

        auto new_node = new LinkedNode(val);
        LinkedNode * cur = dummy_head_;
        while (index--) {
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
        size_++;
    }

    // 如果索引 index 有效，则删除链表中的第 index 个节点。
    void deleteAtIndex(int index) {
        if (index < 0 || index > size_ - 1) return;

        LinkedNode * cur = dummy_head_;
        while (index--) {
            cur = cur->next;
        }
        LinkedNode * temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        temp = nullptr;
        size_--;
    }

    // 打印链表
    void printLinkedList() {
        LinkedNode* cur = dummy_head_;
        while (cur->next != nullptr) {
            cout << cur->next->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
private:
    int size_;
    LinkedNode * dummy_head_;
};