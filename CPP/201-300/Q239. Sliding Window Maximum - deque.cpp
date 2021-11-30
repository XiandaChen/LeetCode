class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> q; // holding idx, q.front(): idx of max val for the window
        int n = nums.size(), i = 0;
        
        // process the first k elements
        for (; i < k; i++) {
            // nums[i] > nums[q.back()], then
            // nums[q.back()] is not max for this sliding window
            while (!q.empty() && nums[i] > nums[q.back()]) q.pop_back();
            q.push_back(i);
        }
        res.push_back(nums[q.front()]); // max num for the first window
        
        for (; i < n; i++) {
            // remove the elements not belong to this window (contraction)
            while (!q.empty() && q.front() <= i - k) q.pop_front();
            
            // remove elements that are in the window but not max
            while (!q.empty() && nums[q.back()] <= nums[i]) q.pop_back();
            
            q.push_back(i);
            
            res.push_back(nums[q.front()]);
        }
        
        return res;
    }
};

