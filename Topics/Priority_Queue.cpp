// 973. K Closest Points to Origin
// Min-queue
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> res;
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1]; // min-queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        for (auto point : points)
            q.push(point);
        for (int i = 0; i < K; ++i) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};

// 23. Merge k Sorted Lists
// Min-queue
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
            // put the next node of the list from which minimum node was poped
            if (curr->next) q.push(curr->next);
        }
        return dummyHead->next;
    }
};

//347. Top K Frequent Elements
// By default C++ creates a max-heap
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q; // int is not struct for queue, use pair<>
        vector<int> res;
        for (auto num : nums) ++m[num];  // use auto, int is not struct
        for (auto it : m) q.push({it.second, it.first}); // use auto, int is not struct
        for (int i = 0; i < k; ++i) {
            res.push_back(q.top().second);
            q.pop();
        }
        return res;
    }
};

// 253. Meeting Rooms II
// Find the minimum number of conference rooms required
// min-heap: priority_queue<int, vector<int>, greater<int>>
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        auto cmp = [] (vector<int> & a, vector<int> & b) {
            return a[0] < b[0]; };
        sort(intervals.begin(), intervals.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> q;
        for (auto intvl : intervals) {
            // being-used room gets free for new meeting
            if (!q.empty() && q.top() <= intvl[0]) q.pop();
            q.push(intvl[1]);
        }
        return q.size();
    }
};

// 767. Reorganize String, Max-heap, can be generalize to any k
// Rearrange string so that any two adjacent characters (k=2) are not the same
class Solution {
public:
    string reorganizeString(string s) {
        int len = s.size(), k = 2;
        map<char, int> m;
        priority_queue<pair<int, char>> q;
        string res = "";
        for (char c : s) ++m[c];
        for (auto a : m)  q.push({a.second, a.first});
        while (!q.empty()) {
            vector<pair<int, char>> tmp; // to hold availabel items after processing
            int cnt = min(k, len); // take k item each time if len>=k
            for (int i = 0; i < cnt; ++i) {
                if (q.empty()) return ""; // check
                auto t = q.top(); q.pop();
                res += t.second;
                if (--t.first) tmp.push_back(t);
                --len;
            }
            for (auto a : tmp) q.push(a);
        }
        return res;
    }
};

// 1094. Car Pooling, trip[i] = [num_passengers, start_location, end_location]
	// ref: Q253, minimum meeting rooms
	// similar: Maximum CPU load
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        auto startCmp = [](vector<int> &a, vector<int> &b) {
           return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]); 
        };
        sort(trips.begin(), trips.end(), startCmp);
        
        auto endCmp = [](vector<int> &a, vector<int> &b) {
            return a[2] > b[2];  // descending in endtime: min queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(endCmp)> q(endCmp); //q(endCmp)
        
        int curload = 0, maxload = 0;
        for (auto trip : trips) {
            // remove all trips that have droped off
            while (!q.empty() && q.top()[2] <= trip[1]) {
                curload -= q.top()[0];
                q.pop();
            }
            
            // add cur trip (passengers) onto vehicle
            q.push(trip);
            curload += trip[0];
            maxload = max(maxload, curload);
            
            // check if overloading
            if (maxload > capacity) return false;
        }
        
        return true;
    }
};
