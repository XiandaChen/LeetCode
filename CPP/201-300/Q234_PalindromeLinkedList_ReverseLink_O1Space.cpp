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
        int cnt = 0;
        ListNode * cur = head;
        while (cur) {
            ++cnt;
            cur = cur->next;
        }
        cur = head;
        while (ceil(cnt / 2.0) > 0) {
            cur = cur->next;
            cnt -= 2;
        }
        ListNode * back = reverseList(cur);
        while (back) {
            if (head->val != back->val) return false;
            head = head->next;
            back = back->next;
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