class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for (int num : nums) sum += num;
        if (sum %2 != 0) return false;
        
        sum /= 2;
        
        vector<vector<bool>> dp(n, vector<bool>(sum + 1));
        
        for (int i = 0; i < n; i++) dp[i][0] =  true;
        for (int s = 1; s <= sum; s++) { // i = 1
            dp[0][s] = (nums[0] == s) ? true : false;
        }
        
        for (int i = 1; i < n; i++) {
            for (int s = 1; s <= sum; s++) { // <=
                bool tmp = false;
                if (nums[i] <= s) { // include i-th num
                    tmp = dp[i - 1][s - nums[i]];
                }
                // exclude or include ith num
                dp[i][s] = dp[i - 1][s] || tmp;
            }
        }
        
        return dp[n - 1][sum];
    }
};