class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // priority_queue<int> q;
        // for (int num : nums) q.push(num);
        priority_queue<int> q(nums.begin(), nums.end());
        for (int i = k; i > 1; --i)
            q.pop();
        return q.top();
    }
};