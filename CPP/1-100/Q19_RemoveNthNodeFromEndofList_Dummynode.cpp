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
        // The "dummy" node to simplify corner cases such as having only one node, 
        // or removing the head of the list. 
        ListNode *dummyHead = new ListNode(0);
        dummyHead->next = head;
        
        ListNode *pre = dummyHead, *cur = dummyHead;
        for (int i = 1; i <= n + 1; i++) {
            cur = cur->next;
        }
        while (cur) {
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = pre->next->next;
        return dummyHead->next;
    }
};