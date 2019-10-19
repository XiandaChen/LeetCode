class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, n = nums.size(), sum = 0;
        unordered_map<int, int> m{{0, 1}}; // sum--count
        for (int i = 0 ; i < n; ++i) {
            sum += nums[i];
            res += m[sum - k]; // 
            ++m[sum];
        }
        return res;
    }
};