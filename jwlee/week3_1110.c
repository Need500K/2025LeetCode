/** Questions
*  Given the root of a binary tree, each node in the tree has a distinct value.
*  After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).
*  Return the roots of the trees in the remaining forest. You may return the result in any order.
*/

/** Constraints
        The number of nodes in the given tree is at most 1000.
        Each node has a distinct value between 1 and 1000.
        to_delete.length <= 1000
        to_delete contains distinct values between 1 and 1000.
*/


// Definition for a binary tree node.
struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM (1000)
struct TreeNode* forest[MAX_NUM];
int tree_num;

int delete_arr[MAX_NUM];
int delete_num;

static inline int isDelete(int val)
{
    for(register int i = 0; i < delete_num; ++i)
    {
        if (val == delete_arr[i])
            return 1;
    }
    return 0;
}

int traverse(struct TreeNode* root)
{
    // LEAF 아래나 지워질애나 동일.
    if (root == NULL)
        return 1;

    // order는 leaf부터 보면서 올라옴.
    // traverse left
    int left = traverse(root->left);
    // traverse right
    int right = traverse(root->right);

    // check value.
    // if Root is target, add left & right node to forest
    int is_delete = isDelete(root->val);
    if (is_delete != 0)
    {
        // 내가 타겟
        if (left == 0) forest[tree_num++] = root->left; 
        if (right == 0) forest[tree_num++] = root->right;
    }
    else 
    {
        if (left != 0) root->left = NULL;
        if (right != 0) root->right = NULL;
    }
    return is_delete; 
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize)
{
    tree_num = 0;
    delete_num = to_deleteSize;

    // copy of O(N)
    for (register int i = 0; i < to_deleteSize; ++i)
    {
        delete_arr[i] = to_delete[i];
    }

    int root_target = isDelete(root->val);
    if (root_target == 0)
        forest[tree_num++] = root;

    traverse(root);
    struct TreeNode** result = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * tree_num);
    *returnSize = tree_num;    
    for (register int i = 0; i < tree_num; ++i)
    {
        result[i] = forest[i];
    }

    return result;
}
