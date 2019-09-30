/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head->next) return NULL;   // only one node
        ListNode *pre = head, *cur = head;
        while (n > 0) {
            cur = cur->next;
            n--;
        }
        if (!cur) return head->next;    // n equals to num of nodes
        while (cur->next) {
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = pre->next->next;
        return head;
    }
};