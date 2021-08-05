class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        priority_queue<pair<int, int>> q; // val-idx, max queue
        for (int i = 0; i < n; ++i) {
            while (!q.empty() && q.top().second <= i - k) q.pop();
            q.push({nums[i], i}); // O(logN)
            if (k - 1 <= i) res.push_back(q.top().first);
        }
        return res;
    }
};