class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        unordered_map<int, int> cnt{{0, 1}}; // sum-cnt
        int res = 0, curSum = 0;
        for (int num : nums) {
            curSum += num;
            res += cnt[curSum - k];
            ++cnt[curSum];
        }
        return res;
    }
};