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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode * dummy = new ListNode(-1), * pre = dummy;
        dummy->next = head;
        for (int i = 1; i < m; ++i) pre = pre->next;
        ListNode * cur = pre->next; // point cur is updated with pre->next
        for (int i = m; i < n; ++i) { // iterate n-m steps
            ListNode * tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = pre->next; // not "tmp->next = cur;"
            pre->next = tmp; // update pre->next (and thus cur)
        }
        return dummy->next;
    }
};