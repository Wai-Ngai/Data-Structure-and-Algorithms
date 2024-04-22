/**
 *   二叉树 ： 链表实现
 *   Created by wai-ngai on 24-4-15.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char E;

typedef struct TreeNode {
    E element;                // 存放元素
    struct TreeNode * left;   // 指向左子树的指针
    struct TreeNode * right;  // 指向右子树的指针
    int flag;                // 需要经历左右子树都被遍历才行，用于自定义栈后续遍历，0表示左子树遍历完成，1表示右子树遍历完成
} * Node;

//------------- 栈 -------------------
typedef Node T;   //这里栈内元素类型定义为上面的Node，也就是二叉树结点指针

struct StackNode {
    T element;
    struct StackNode * next;
};

typedef struct StackNode * SNode;  //这里就命名为SNode，不然跟上面冲突了就不好了

void initStack(SNode head){
    head->next = NULL;
}

bool pushStack(SNode head, T element){
    SNode node = malloc(sizeof(struct StackNode));
    if(node == NULL) return 0;
    node->next = head->next;
    node->element = element;
    head->next = node;
    return 1;
}

bool isEmpty(SNode head){
    return head->next == NULL;
}

T popStack(SNode head){
    SNode top = head->next;
    head->next = head->next->next;
    T e = top->element;
    free(top);
    return e;
}

T peekStack(SNode head){   //这里新增一个peek操作，用于获取栈顶元素的值，但是不出栈，仅仅是值获取
    return head->next->element;
}

//-------------------------------------

//--------------- 队列 ----------------
typedef Node T;   //还是将Node作为元素

struct QueueNode {
    T element;
    struct QueueNode * next;
};

typedef struct QueueNode * QNode;

struct Queue{
    QNode front, rear;
};

typedef struct Queue * LinkedQueue;

bool initQueue(LinkedQueue queue){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    queue->front = queue->rear = node;
    return 1;
}

bool offerQueue(LinkedQueue queue, T element){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    node->element = element;
    queue->rear->next = node;
    queue->rear = node;
    return 1;
}

bool isEmptyQ(LinkedQueue queue){
    return queue->front == queue->rear;
}

T pollQueue(LinkedQueue queue){
    T e = queue->front->next->element;
    QNode node = queue->front->next;
    queue->front->next = queue->front->next->next;
    if(queue->rear == node) queue->rear = queue->front;
    free(node);
    return e;
}
//--------------------------------


/**
 *  前序遍历 （中左右）: 递归调用实现
 *           1.打印根节点
 *           2.前序遍历左子树
 *           3.前序遍历右子树
 * @param root
 */
void preOrder(Node root){   //传入的是二叉树的根结点
    if (root == NULL) return;
    printf("%c", root->element);
    preOrder(root->left);  // 将左孩子递归给下一级
    preOrder(root->right); //等上面的一系列向左递归结束后，再以同样的方式去到右边
}

/**
 *  前序遍历 （中左右）: 自定义栈实现
 *           1.一路向左，不断入栈，直到尽头
 *           2.到达尽头后，出栈，看看有没有右子树，如果没有就继续出栈，直到遇到有右子树的为止
 *           3.拿到右子树后，从右子树开始，重复上述步骤，直到栈清空
 * @param root
 */
void preOrder2(Node root){   //传入的是二叉树的根结点
    struct StackNode stack;
    initStack(&stack);  //栈先搞出来

    while (root || !isEmpty(&stack)) {         // 两个条件，只有当栈空并且节点为NULL时才终止循环
        while (root) {                              // 先不断遍历左子树，直到为NULL
            pushStack(&stack,root);   // 途中，每经过一个节点，就将节点丢进栈中
            printf("%c", root->element);     // 然后打印当前结点元素值
            root = root->left;                      // 继续遍历下一个左孩子结点
        }
        root = popStack(&stack);   // 经过前面的循环，明确左子树全部遍历完，接着就是右子树了
        root = root->right;             // 取出栈顶元素，得到右孩子，如果有右孩子，下一轮会重复上面的步骤；
                                        // 如果没有右孩子那么这里的root就被赋值为NULL了，下一轮开始会直接跳过上面的while，继续出栈下一个结点再找右子树
    }
}


/**
 *  中序遍历（左中右）：递归实现
 *          1.中序遍历左子树
 *          2.打印结点
 *          3.中序遍历右子树
 * @param root
 */
void inOrder(Node root) {
    if (root == NULL) return;
    inOrder(root->left);             // 先完成全部左子树的遍历
    printf("%c", root->element);   // 等待左子树遍历完成之后再打印
    inOrder((root->right));          // 然后就是对右子树进行遍历
}


/**
 *  中序遍历 （左中右）： 非递归
 * @param root
 */
void inOrder2(Node root) {
    struct StackNode stack;
    initStack(&stack);

    while (root || !isEmpty(&stack)) {
        while (root) {
            pushStack(&stack, root);
            root = root->left;
        }
        root = popStack(&stack);
        printf("%c", root->element);
        root = root->right;
    }
}


/**
 *  后序遍历（左右中）：需要等待左右子树全部遍历完成，才会去进行打印。
 * @param root
 */
void postOrder(Node root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c", root->element);
}


/**
 *  后序遍历（左右中）：非递归，自定义栈，所以需要一个标志来标志右子树是否已经遍历完成，才能打印
 * @param root
 */
void postOrder2(Node root) {
    struct StackNode stack;
    initStack(&stack);

    while (root || !isEmpty(&stack)) {
        while (root) {
            pushStack(&stack, root);
            root->flag = 0;                      //首次入栈时，只能代表左子树遍历完成，所以flag置0
            root = root->left;
        }
        root = peekStack(&stack);  //注意这里只是获取到结点，并没有进行出栈操作，因为需要等待右子树遍历完才能出栈
        if (root->flag == 0) {          //如果仅仅遍历了左子树，那么flag就等于0
            root->flag = 1;             //此时标记为1表示遍历右子树
            root = root->right;
        } else {
            printf("%c", root->element);  //当flag为1时走这边，此时左右都遍历完成了，这时再打印值出来
            popStack(&stack);              //这时再把对应的结点出栈，因为左右都完事了
            root = NULL;                        //置为NULL，下一轮直接跳过while，然后继续取栈中剩余的结点，重复上述操作
        }
    }
}


/**
 *  层序遍历：利用队列来实现层序遍历，首先将根结点存入队列中，接着循环执行以下步骤：
 *           1.进行出队操作，得到一个结点，并打印结点的值。
 *           2.将此结点的左右孩子结点依次入队。
 *           3.不断重复以上步骤，直到队列为空。
 * @param root
 */
void levelOrder(Node root) {
    struct Queue queue;
    initQueue(&queue);
    offerQueue(&queue, root);   // 先把根节点入队

    while (!isEmptyQ(&queue)) {    // 不断重复，直到队列空为止
        Node node = pollQueue(&queue);  // 出队一个元素，打印值
        printf("%c", node->element);
        if (node->left) offerQueue(&queue, node->left); //如果存在左右孩子的话,将左右孩子入队，注意顺序，先左后右
        if (node->right) offerQueue(&queue, node->right);
    }
}



int main() {

    Node a = malloc(sizeof(struct TreeNode));
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    Node f = malloc(sizeof(struct TreeNode));

    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';
    f->element = 'F';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    c->left = NULL;
    d->left = e->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;

//    preOrder(a);
//    preOrder2(a);

//    inOrder(a);
//    inOrder2(a);

//    postOrder(a);
    postOrder2(a);

//    levelOrder(a);

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);
    return 0;
}