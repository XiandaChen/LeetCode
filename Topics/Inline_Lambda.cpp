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


// 252. Meeting Rooms
// Determine if a person could attend all meetings
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[0] < b[0];	};	// sorting: increasing
        sort(intervals.begin(), intervals.end(), cmp);
        for (int i = 1; i < intervals.size(); ++i) 
			if (intervals[i - 1][1] > intervals[i][0]) return false;
        return true;
    }
};