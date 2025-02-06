



 struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };
 


 /**
  * Note: The returned array must be malloced, assume caller calls free().
  */
#include <malloc.h>


struct TreeNode** delNodes(struct TreeNode* root, int* to_delete, int to_deleteSize, int* returnSize) {

    struct TreeNode* tree_arr[1002] = { 0 };
    int tree_dp[1002] = { 0 };

    struct TreeNode* queue[1002];
    int front = 0, rear = 1;
    queue[0] = root;
    
    int cnt = 0;

    while (front < rear) {
        struct TreeNode* tmp = queue[front++];
        tree_arr[cnt] = tmp;
        tree_dp[tmp->val] = cnt++;
        if (tmp->left) queue[rear++] = tmp->left;
        if (tmp->right) queue[rear++] = tmp->right;
    }

    int is_root[1002] = { 0 };
    is_root[0] = 1;
    
    for (int i = 0; i < to_deleteSize; i++) {
        int del_idx = tree_dp[to_delete[i]];
        struct TreeNode* tmp = tree_arr[del_idx];
        if (tmp->left) is_root[tmp->left->val] = 1;
        if (tmp->right) is_root[tmp->right->val] = 1;
        tree_arr[del_idx] = 0;
    }
    struct TreeNode** ret_arr = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * 1002);
    int ret_cnt = 0;
    for (int i = 0; i < cnt; i++) {
        if (tree_arr[i] && is_root[tree_arr[i]->val]) {
            ret_arr[ret_cnt++] = tree_arr[i];
        }
    }
    *returnSize = ret_cnt;
    
    return ret_arr;

}

#include <stdio.h>
int main() {
    struct TreeNode arr[100];
    for (int i = 0; i < 7; i++) {
        arr[i].val = i + 1;
        arr[i].left = arr[i].right = 0;
    }
    arr[0].left = &arr[1];
    arr[0].right = &arr[2];
    arr[1].left = &arr[3];
    arr[1].right = &arr[4];
    arr[2].left = &arr[5];
    arr[3].right = &arr[6];
    int del[2] = { 3, 5 };
    int cnt;
    delNodes(arr, del, 2, &cnt);
}
