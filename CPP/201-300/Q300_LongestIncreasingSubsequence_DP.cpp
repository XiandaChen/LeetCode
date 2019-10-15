class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1); // longest subsquenece ending up at position i
        int res = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) // or <= when duplicate num exist
                    dp[i] = max(dp[i], dp[j] + 1); // 
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};