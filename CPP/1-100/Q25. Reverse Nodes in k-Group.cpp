class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode * dummy = new ListNode(-1, head), * pre = dummy, * cur = dummy;
        int num = 0;
        while (cur->next) {cur = cur->next; ++num;}  // node#
        while (num >= k) {
            cur = pre->next;
            for (int i = 1; i < k; ++i) {
                ListNode * next = cur->next;
                cur->next = next->next;
                next->next = pre->next;
                pre->next = next;
            }
            pre = cur; // move to next k-group
            num -= k;
        }
        return dummy->next;
    }
};