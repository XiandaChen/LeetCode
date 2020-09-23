class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head) return NULL;
        int n = 1;
        ListNode * cur = head;
        while (cur->next) { // get node num and the last node
            cur = cur->next;
            ++n;
        }
        cur->next = head;  // construct circular list
        int m = n - k % n;        // no rotation for more than n
        for (int i = 0; i < m; ++i) 
            cur = cur->next;
        // cut off circular list
        ListNode * newhead = cur->next;
        cur->next = NULL;
        return newhead;
    }
};