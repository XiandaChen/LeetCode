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
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *dummy = new ListNode(-1), *prev = dummy;
        dummy->next = head;
        while (prev->next) {
            if (prev->next->val == val) {
                ListNode * tmp = prev->next;
                prev->next = tmp->next;
                tmp->next = NULL;
                delete tmp;
            }
            else {
                prev = prev->next;
            }
        }
        return dummy->next;
    }
};