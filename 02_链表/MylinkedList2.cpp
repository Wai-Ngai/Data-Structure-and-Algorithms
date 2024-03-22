//
// 双链表实现
//
class MyLinkedList {
    struct ListNode {
        int val;
        ListNode *prev;
        ListNode *next;

        ListNode(int x) : val(x), prev(this), next(this) {}
    };

public:
    /** Initialize your data structure here. */
    MyLinkedList() {
        dummy = new ListNode(-1);
        _size = 0;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        ListNode *pos = dummy;
        while (index-- >= 0) {
            pos = pos->next;
            if (pos == dummy)
                return dummy->val;
        }
        return pos->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        ListNode *node = new ListNode(val);
        node->next = dummy->next;
        dummy->next = node;
        node->next->prev = node;
        node->prev = dummy;
        _size++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        ListNode *node = new ListNode(val);
        node->prev = dummy->prev;
        dummy->prev = node;
        node->prev->next = node;
        node->next = dummy;
        _size++;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        ListNode *pos = dummy;
        if (index == _size) {
            addAtTail(val);
        } else {
            //定位到插入位置
            while (index-- >= 0) {
                pos = pos->next;
                if (pos == dummy) {
                    return;
                }
            }
            ListNode *node = new ListNode(val);
            node->prev = pos->prev;
            pos->prev = node;
            node->prev->next = node;
            node->next = pos;
            _size++;
        }
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        ListNode *pos = dummy;
        //定位到插入位置
        while (index-- >= 0) {
            pos = pos->next;
            if (pos == dummy)
                return;
        }
        ListNode *temp = pos->next;
        pos->next->prev = pos->prev;
        pos->prev->next = temp;
        _size--;

    }

private:
    int _size;
    ListNode *dummy;
};