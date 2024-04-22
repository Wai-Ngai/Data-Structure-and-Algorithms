/**
 *   二叉树线索化 ： 链表实现
 *   Created by wai-ngai on 24-4-22.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char E;

typedef struct TreeNode {
    E element;
    struct TreeNode* left;
    struct TreeNode* right;
    int left_flag;     //标志位，如果为1表示这一边指针指向的是线索，不为1就是正常的孩子结点
    int right_flag;
} * Node;


/**
 *  创建树的节点
 * @param element
 * @return
 */
Node creatNode(E element) {
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->left_flag = node->right_flag = 0;
    node->element = element;
    return  node;
}


/**
 *  前序遍历线索化函数
 * @param root
 */
 Node pre = NULL; //这里我们需要一个pre来保存后续结点的指向
void preOrderThreaded (Node root) {
    if (root == NULL) return;

    if (root->left == NULL) { //首先判断当前结点左边是否为NULL，如果是，那么指向上一个结点
        root->left = pre;
        root->left_flag = 1; //记得修改标记
    }
    if (pre && pre->right == NULL) { //然后是判断上一个结点的右边是否为NULL，如果是那么进行线索化，指向当前结点
        pre->right = root;
        pre->right_flag = 1;
    }
    pre = root;  //每遍历完一个，需要更新一下pre，表示上一个遍历的结点

    if (root->left_flag == 0) preOrderThreaded(root->left);  //注意只有标志位是0才可以继续向下，否则就是线索了
    if (root->right_flag == 0) preOrderThreaded(root->right);
}

/**
 *  前序遍历一棵线索化二叉树
 * @param root
 */
void preOrder (Node root) {
    while (root) {
        printf("%c", root->element); //因为是前序遍历，所以直接按顺序打印就行了
        if (root->left_flag ==0) {
            root = root->left; //如果是左孩子，那么就走左边
        } else {
            root = root->right; //如果左边指向的不是孩子，而是线索，那么就直接走右边，因为右边无论是线索还是孩子，都要往这边走了
        }
    }
}

/**
 *   中序遍历线索化函数
 */
Node pre1 = NULL; //这里我们需要一个pre来保存后续结点的指向
void inOrderThreaded (Node root) {
    if (root == NULL) return;

    if (root->left_flag == 0) inOrderThreaded(root->left);  //注意只有标志位是0才可以继续向下，否则就是线索了

    if (root->left == NULL) { //首先判断当前结点左边是否为NULL，如果是，那么指向上一个结点
        root->left = pre1;
        root->left_flag = 1; //记得修改标记
    }
    if (pre1 && pre1->right == NULL) { //然后是判断上一个结点的右边是否为NULL，如果是那么进行线索化，指向当前结点
        pre1->right = root;
        pre1->right_flag = 1;
    }
    pre1 = root;  //每遍历完一个，需要更新一下pre，表示上一个遍历的结点

    if (root->right_flag == 0) inOrderThreaded(root->right);
}

/**
 *  中序遍历一棵线索化二叉树
 * @param root
 */
void inOrder(Node root) {
    while (root) { // 因为中序遍历需要先完成左边，所以说要先走到最左边才行
        while (root && root->left_flag == 0) { //如果左边一直都不是线索，那么就一直往左找，直到找到一个左边是线索的为止，表示到头了
            root = root->left;
        }
        printf("%c", root->element); //到最左边了再打印，中序开始

        while (root && root->right == 1) { //打印完就该右边了，右边如果是线索化之后的结果，表示是下一个结点，那么就一路向前，直到不是为止
            root = root->right;
            printf("%c", root->element);  //注意按着线索往下就是中序的结果，所以说沿途需要打印
        }
        root = root->right; //最后继续从右结点开始，重复上述操作
    }
}


/**
 *   后序遍历线索化函数
 */
Node pre2 = NULL; //这里我们需要一个pre来保存后续结点的指向
void postOrderThreaded (Node root) {
    if (root == NULL) return;

    if (root->left_flag == 0) postOrderThreaded(root->left);  //注意只有标志位是0才可以继续向下，否则就是线索了
    if (root->right_flag == 0) postOrderThreaded(root->right);

    if (root->left == NULL) { //首先判断当前结点左边是否为NULL，如果是，那么指向上一个结点
        root->left = pre2;
        root->left_flag = 1; //记得修改标记
    }
    if (pre2 && pre2->right == NULL) { //然后是判断上一个结点的右边是否为NULL，如果是那么进行线索化，指向当前结点
        pre2->right = root;
        pre2->right_flag = 1;
    }
    pre2 = root;  //每遍历完一个，需要更新一下pre，表示上一个遍历的结点
}

/**
 *  后序遍历一棵线索化二叉树
 * @param root
 */
void postOrder(Node root){
    Node last = NULL, node = root;  //这里需要两个暂存指针，一个记录上一次遍历的结点，还有一个从root开始
    while (node) {
        while (node->left != last && node->left_flag == 0)    //依然是从整棵树最左边结点开始，和前面一样，只不过这里加入了防无限循环机制，看到下面就知道了
            node = node->left;
        while (node && node->right_flag == 1) {   //左边完了还有右边，如果右边是线索，那么直接一路向前，也是跟前面一样的
            printf("%c", node->element);   //沿途打印
            last = node;
            node = node->right;
        }
        if (node == root && node->right == last) {
            //上面的操作完成之后，那么当前结点左右就结束了，此时就要去寻找其兄弟结点了，我们可以
            //直接通过parent拿到兄弟结点，但是如果当前结点是根结点，需要特殊处理，因为根结点没有父结点了
            printf("%c", node->element);
            return;   //根节点一定是最后一个，所以说直接返回就完事
        }
        while (node && node->right == last) {    //如果当前结点的右孩子就是上一个遍历的结点，那么一直向前就行
            printf("%c", node->element);   //直接打印当前结点
            last = node;
            node = node->parent;
        }
        //到这里只有一种情况了，是从左子树上来的，那么当前结点的右边要么是线索要么是右子树，所以直接向右就完事
        if(node && node->rightTag == 0) {  //如果不是线索，那就先走右边，如果是，等到下一轮再说
            node = node->right;
        }
    }
}


int main() {
    Node A = creatNode('A');
    Node B = creatNode('B');
    Node C = creatNode('C');
    Node D = creatNode('D');
    Node E = creatNode('E');

    A->left = B;
    A->right = C;
    B->left = D;
    B->right = E;

    preOrderThreaded(A);
    preOrder(A);


    return 0;
}
