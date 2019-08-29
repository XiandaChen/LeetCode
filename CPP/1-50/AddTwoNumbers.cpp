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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *dummyHead = new ListNode(0);
        ListNode *p = l1, *q = l2, *curr = dummyHead;
        int carry = 0;
        while (p != NULL || q != NULL) {
            int x = (p != NULL) ? p->val : 0;
            int y = (q != NULL) ? q->val : 0;
            int z = (x + y + carry) % 10;
            carry = (x + y + carry) / 10;   
            curr->next = new ListNode(z);   // add new node
            curr = curr->next;              // set current cursor
            p = (p != NULL) ? p->next : NULL;
            q = (q != NULL) ? q->next : NULL;
        }
        if (carry >0 )      // extra carry at the end
            curr->next = new ListNode(carry);
        
        return dummyHead->next;
    }
};