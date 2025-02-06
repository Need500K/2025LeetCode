/**
* Given a binary tree root and a linked list with head as the first node. 
* Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.
* In this context downward path means a path that starts at some node and goes downwards.
*
* Constraints:
*   The number of nodes in the tree will be in the range [1, 2500].
*   The number of nodes in the list will be in the range [1, 100].
*   1 <= Node.val <= 100 for each node in the linked list and binary tree.
*/

/**
* Sol: Traverse & Find Path
* 
* 근데 뭔가 이상한게... 아마도 O(N log N) 혹은 O(N * M)정도 일 것 같은데...
* 전역 uint8_t STACK이 없으면 느려짐. 근데 STACK은 사용안되고 있음. Align 문제가 있나?
*       Align 문제 맞는 것 같다. 모든 값을 INT로 변경 시, 시간은 그대로, Memory사용량만 증가. 
*       32 machine에서 8 8 8 로만 사용되면서 내부 code align이 깨졌나?
* 16 Align으로 가져가도 괜찮다.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
//Definition for singly-linked list.
struct ListNode 
{
    int val;
    struct ListNode *next;
};

// Definition for a binary tree node.
struct TreeNode 
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX_NUM (100)

// Constraint value [1,100]
uint8_t path[MAX_NUM] = {0, };
uint8_t len;

int stack_idx;

bool find_path(struct TreeNode* root)
{
    if (root == NULL)
        return false;

    bool is_pushed = false;
    if (root->val == path[stack_idx])
    {
        is_pushed = true;
        stack_idx++;
    }
    else 
        return false;

    if (stack_idx == len)
        return true;

    bool is_left = find_path(root->left);
    bool is_right = find_path(root->right);
    if (is_pushed)
    {
        stack_idx--;
        stack_idx = stack_idx < 0 ? 0:stack_idx; // prevent negative
    }

    return is_left || is_right;
}

bool traverse(struct TreeNode* root)
{
    if (root == NULL)
        return false;
    bool result = false;
    // found head
    if (root->val == path[0]) 
    {
        stack_idx = 0;
        result = find_path(root);
    }

    // stop when find
    if (result)
        return true;

    bool is_left = traverse(root->left);
    bool is_right = traverse(root->right);
    return is_left || is_right;
}

bool isSubPath(struct ListNode* head, struct TreeNode* root) 
{
    bool result = false; 
    
    // To Keep original pointer of head (May Not use)
    struct ListNode* tmp_head = head;

    // Copy List into array [O(n)] max n = 100
    len = 0;
    while (tmp_head != NULL)
    {
        path[len++] = tmp_head->val;
        tmp_head = tmp_head->next;
    }

    stack_idx = 0;
    result = traverse(root);
   
    return result;
}

int main()
{
    int haedLen = 5;
    int rawHead[] = {1,4,2,6,8};

    int treeLen = 17;
    int rawTree[] = {1,4,4,0,2,2,0,1,0,6,8,0,0,0,0,1,3};

}
