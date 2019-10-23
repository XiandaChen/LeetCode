/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) return NULL;
        return sortedListToBST(head, NULL);
    }
    TreeNode * sortedListToBST(ListNode * head, ListNode * tail) {
        if (head == tail) return NULL;
        ListNode * slow = head, * fast = head;
        while (fast != tail && fast->next != tail) { // compare with tail, not NULL
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode * cur = new TreeNode(slow->val); // mid list node (slow)
        cur->left = sortedListToBST(head, slow);
        cur->right = sortedListToBST(slow->next, tail);
        return cur;
    }
};