class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode * dummy = new ListNode(-1, head), * pre = dummy, * cur = pre->next;
        while (cur && cur->next) {
            ListNode * next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
            pre = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};