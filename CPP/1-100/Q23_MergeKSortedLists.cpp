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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Using lambda to compare elements
        auto cmp = [](ListNode* & a, ListNode* & b) {
            return a->val > b->val; // min queue: increasing order
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        // put first node of each list into priority queue
        for (auto node : lists) {
            // must check if node exists
            if (node) q.push(node);
        }
        
        ListNode *dummyHead = new ListNode(-1), *curr = dummyHead;
        while (!q.empty()) {
            // add the minimum node
            curr->next = q.top();
            q.pop();
            curr = curr->next;
            // put the next node of the list from which minimum node was poped out the queue
            if (curr->next) q.push(curr->next);
        }
        return dummyHead->next;
    }
};