/**
 *   平衡二叉树 / AVL树
 *
 *      平衡二叉树一定是一棵二叉查找树。
 *      任意结点的左右子树也是一棵平衡二叉树。
 *      从根节点开始，左右子树都高度差不能超过1，否则视为不平衡。
 *
 *   Created by wai-ngai on 24-4-22.
 */

#include <stdio.h>
#include <stdlib.h>


typedef int E;

typedef struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
    int height;   // 每个节点都需要记录当前子树的高度，便于计算平衡因子
} * Node;


Node creatNode (E element) {
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    node->height = 1;
    return node;
}


int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Node root) {
    if (root == NULL) return 0;
    return root->height;
}

/**
 *  平衡二叉树 : 左旋操作，实际上就是把右边结点拿上来
 * @param element
 * @return
 */
Node leftRotation(Node root) {
    Node new_root = root->right;   // 拿到右边节点
    root->right = new_root->left;  // 将右边节点的左子树，丢到原根节点的右边去
    new_root->left = root;         // 将新根节点的左边指向原根节点

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;             // 原根节点高度
    new_root->height = max(getHeight(new_root->right), getHeight(new_root->left)) + 1; // 新根节点高度

    return new_root;
}

/**
 *  平衡二叉树 : 右旋操作，实际上就是把左边结点拿上来
 * @param element
 * @return
 */
Node rightRotation(Node root) {
    Node new_node = root->left;   // 拿到左边节点，作为新的根节点
    root->left = new_node->right; // 原根节点的左边指向新节点的右子树
    new_node->right = root;

    root->height = max(getHeight(root->right), getHeight(root->left)) + 1;
    new_node->height = max(getHeight(new_node->right), getHeight(new_node->left)) + 1;

    return new_node;
}

Node leftRightRotation(Node root) {
    root->left = leftRotation(root->left);  // 注意这里左旋，是根节点下面两个节点左旋，将下下个节点旋转上来与根节点连接
    return rightRotation(root);  // 这里右旋，是包括根节点在内的3个节点右旋，将中间节点作为新的根节点
}

Node rightLeftRotation(Node root) {
    root->right = rightRotation(root->right);
    return leftRotation(root);
}


/**
 *  平衡二叉树 : 插入时动态计算树的高度，一旦发现不平衡，那么就立即采取对应措施：
 * @param root
 * @param element
 * @return
 */
Node insert(Node root, E element) {
    if (root == NULL) {
        root = creatNode(element);  //如果结点为NULL，说明找到了插入位置，直接创建新的就完事
    } else if (root->element > element) {               //和二叉搜索树一样，判断大小，该走哪边走哪边，直到找到对应插入位置
        root->left = insert(root->left, element);

        if (getHeight(root->left) - getHeight(root->right) > 1) {  // 插入完成之后，需要计算平衡因子，看看是否失衡
            if (root->left->element > element)   // 接着需要判断一下是插入了左子树的左边还是右边，如果是左边那边说明是LL，如果是右边那说明是LR
                root = rightRotation(root);      // LL型得到左旋之后的结果，得到新的根结点
            else
                root = leftRightRotation(root);  // LR型得到先左旋再右旋之后的结果，得到新的根结点
        }
    } else if (root->element < element) {
        root->right = insert(root->right, element);

        if (getHeight(root->left) - getHeight(root->right) < -1) {
            if (root->right->element < element) {
                root = leftRotation(root);
            } else {
                root = rightLeftRotation(root);
            }
        }
    }
    root->height = max(getHeight(root->right), getHeight(root->left)) + 1; //前面的操作完成之后记得更新一下树高度

    return root; //最后返回root到上一级
}


// 中序遍历
void inOrder(Node root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->element);
    inOrder(root->right);
}


int main() {
    // 测试LL型 ： 右旋
    Node root = insert(NULL, 15);   //插入后，得到根结点
    insert(root, 13);
    insert(root, 20);
    insert(root, 11);
    insert(root, 14);
    root = insert(root, 8);  // 这里要接收返回的root节点

    inOrder(root);

    return 0;
}