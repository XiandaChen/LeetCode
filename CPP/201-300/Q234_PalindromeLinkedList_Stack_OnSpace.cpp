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
        stack<int> st;
        ListNode * cur = head;
        while (cur) {
            st.push(cur->val);
            cur = cur->next;
        }
        while (head) {
            if (head->val != st.top()) return false;
            st.pop();
            head = head->next;
        }
        return true;
    }
};