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
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode * slow = head, * fast = head;
        while (fast->next && fast->next->next) { // step 1: find mid
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode * mid = slow->next; // mid node
        slow->next = NULL; // divide the list
        // step 2: reverse the second part
        ListNode * last = mid, * pre = NULL;
        while (last) {
            ListNode * tmp = last->next; // save last->next
            last->next = pre;
            pre = last; // when finishing, pre points to the last node
            last = tmp;
        }
        // step 3: add element of second part to first part
        while (head && pre) {
            ListNode * tmp = head->next; // save head->next
            head->next = pre;
            pre = pre->next;
            head->next->next = tmp; // link newnode to oldlist
            head = tmp; // move head to oldhead->next
        }
    }
};