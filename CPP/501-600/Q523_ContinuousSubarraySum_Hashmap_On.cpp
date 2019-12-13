class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0;
        unordered_map<int, int> m{{0, -1}}; // sum%k--indx
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            int remainder = (k == 0) ? sum : (sum % k);
            if (m.count(remainder)) {
                if (i - m[remainder] > 1) return true; // length of at least 2
            }
            else {
                m[remainder] = i;
            }
        }
        return false;
    }
};