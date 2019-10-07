/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//https://www.cnblogs.com/hiddenfox/p/3408931.html
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        if (!fast || !fast->next) return NULL; // no cycle
        slow = head;
        while (slow != fast) { // find cycle begin node, fast=2slow
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};