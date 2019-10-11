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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode * slow = head, * fast = head;
        while (fast->next && fast->next->next) { // find last half of the link
            slow = slow->next;
            fast = fast->next->next;
        }
        slow = reverseList(slow->next); // reverse linked list from pos slow->next
        while (slow) {
            if (head->val != slow->val) return false;
            head = head->next;
            slow = slow->next;
        }
        return true;
    }
    ListNode * reverseList(ListNode * head) {
        ListNode * newHead = NULL;
        while (head) {
            ListNode * tmp = head->next;
            head->next = newHead;
            newHead = head;
            head = tmp;
        }
        return newHead;
    }
};