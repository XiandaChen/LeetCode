/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 // Input: head = [1,2,3,4,5,6,7], k = 3; Output: [3,2,1,6,5,4,7]
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
