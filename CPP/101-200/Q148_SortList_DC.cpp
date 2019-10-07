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
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode * slow = head, * fast = head, * mid = head;
        while (fast && fast->next) { // slow at middle when fast hits the end
            mid = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        mid->next = NULL; // divide the list, and conquer (merge)
        return mergeTwoSortedLists(sortList(head), sortList(slow));
    }
    ListNode * mergeTwoSortedLists(ListNode * l1, ListNode * l2) {
        ListNode * dummyHead = new ListNode(-1);
        ListNode * cur = dummyHead;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            }
            else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (!l1) cur->next = l2;
        if (!l2) cur->next = l1;
        return dummyHead->next;
    }
};