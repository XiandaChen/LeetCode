class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int, int>> dp(nums.size()); // start--sumWays
        return findTargetSumWays(nums, S, 0, dp);
    }
    int findTargetSumWays(vector<int> & nums, unsigned int sum, int start, vector<unordered_map<int, int>> &dp) {
        if (start == nums.size()) return sum == 0;
        if (dp[start].count(sum)) return dp[start][sum];
        int cnt1 = findTargetSumWays(nums, sum - nums[start], start + 1, dp);
        int cnt2 = findTargetSumWays(nums, sum + nums[start], start + 1, dp);
        return dp[start][sum] = cnt1 + cnt2;
    }
};