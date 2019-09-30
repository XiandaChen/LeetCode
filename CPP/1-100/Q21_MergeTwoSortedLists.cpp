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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *dummyHead = new ListNode(0);
        ListNode *p = l1, *q = l2, *curr = dummyHead;
        while (p && q) {
            if (p->val < q->val) {
                curr->next = p;
                p = p->next;
            }
            else {
                curr->next = q;
                q = q->next;
            }
            curr = curr->next;
        }
        if (!p) curr->next = q;
        if (!q) curr->next = p;
        
        return dummyHead->next;
    }
};