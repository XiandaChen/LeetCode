class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), target = sum >> 1;
        if (sum & 1) return false; // sum must be even
        vector<bool> dp(target + 1, false); // dp[i]: nums exits subset that equals to i
        dp[0] = true;
        for (int num : nums) 
            for (int i = target; i >= num; --i)
                dp[i] = dp[i] || dp[i - num];
        return dp.back();
    }
};