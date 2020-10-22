class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return false;
        unordered_map<int, int> m; // sum%k -- first index
        m[0] = -1;
        int sum = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            if (k != 0) sum %= k; // remainder
            if (m.count(sum)) {
                if (i - m[sum] > 1) return true; // at leat size 2
            }
            else m[sum] = i;  // must, only recorde the first occurrance
        }
        return false;
    }
};