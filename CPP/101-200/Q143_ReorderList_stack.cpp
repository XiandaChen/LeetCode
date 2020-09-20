class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        stack<ListNode*> st;
        ListNode * cur = head;
        while (cur) {
            st.push(cur);
            cur = cur->next;
        }
        int cnt = ((int)st.size() - 1) / 2;
        cur = head;
        while (cnt-- > 0) {
            auto t = st.top(); st.pop();
            ListNode * tmp = cur->next;
            cur->next = t;
            t->next = tmp;
            cur = tmp;
        }
        st.top()->next = NULL; // must
    }
};