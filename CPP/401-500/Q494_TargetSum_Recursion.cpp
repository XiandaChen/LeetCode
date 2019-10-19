class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int res = 0;
        findTargetSumWays(nums, S, 0, res);
        return res;
    }
    void findTargetSumWays(vector<int> & nums, unsigned int S, int start, int & res) { // use unsigned int, in case of "S=INT_MAX"
        if (start >= nums.size()) {
            if (S == 0) ++ res; // target found
            return;
        }
        findTargetSumWays(nums, S - nums[start], start + 1, res); // assume '+' for num[start]
        findTargetSumWays(nums, S + nums[start], start + 1, res); // assume '-' for num[start]
    }
};