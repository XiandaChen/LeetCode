class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        deque<int> q; // idxs, maintain only useful elements (>=nums[i])
        for (int i = 0; i < n; ++i) {
            if (!q.empty() && q.front() == i - k) q.pop_front();
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i); // log(1)
            if (k - 1 <= i) res.push_back(nums[q.front()]);
        }
        return res;
    }
};