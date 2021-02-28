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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) { // !!
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode * newHead = reverseLinkedList(slow); // reverse the second part
        while (head && newHead) {
            if (head->val != newHead->val) return false;
            head = head->next;
            newHead = newHead->next;
        }
        return true;
    }
    ListNode * reverseLinkedList(ListNode * head) {
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