
//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

 
 //  Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct KMPTreeNode {
    struct TreeNode* node;
    int progress;
};
 
bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    int pattern[101], len_pattern = 0;
    while (head) {
        pattern[len_pattern++] = head->val;
        head = head->next;
    }

    int kmptable[101] = { 0 };

    kmptable[0] = -1;

    int k = 0;
    
    for (int i = 1; i < len_pattern; i++) {
        
        while (pattern[i] != pattern[k] && k > 0) {
            k = kmptable[k];
        }
        if (pattern[i] == pattern[k])
            kmptable[i + 1] = ++k;
    }

    struct KMPTreeNode queue[2500];
    queue[0].node = root;
    queue[0].progress = 0;
    int front = 0, rear= 1;
    while (front != rear) {

        struct TreeNode* front_node = queue[front].node;
        int front_progress = queue[front].progress;
        if (pattern[front_progress] == front_node->val) {
            ++front_progress;
            if (front_progress == len_pattern) {
                return 1;
            }
            
        }
        else {
            while (kmptable[front_progress] >= 0) {
                front_progress = kmptable[front_progress];
                if (pattern[front_progress] == front_node->val) {
                    ++front_progress;
                    break;
                }
           }
            
        }

        if (front_node->left) {
            queue[rear].node = front_node->left;
            queue[rear++].progress = front_progress;
        }
        if (front_node->right) {
            queue[rear].node = front_node->right;
            queue[rear++].progress = front_progress;
        }
        ++front;

    }

    return 0;


}

#include <stdio.h>
int main() {
    struct ListNode link[100];
    struct TreeNode tree[100];
    
    link[0].val = 4;
    link[0].next = &link[1];
    link[1].val = 2;
    link[1].next = 0;

    for (int i = 0; i < 10; i++) {
        tree[i].left = 0;
        tree[i].right = 0;
    }
    tree[0].val = 4;
    tree[1].val = 4;
    tree[2].val = 4;
    tree[3].val = 1;
    tree[7].val = 2;
    tree[0].left = &tree[1];
    tree[0].right = &tree[2];
    tree[1].left = &tree[3];
    tree[3].left = &tree[7];
    printf("%d\n", isSubPath(&link[0], &tree[0]));
}