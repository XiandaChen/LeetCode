class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> m; // sum[0:i]--i
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum == k) res = i + 1; // subarray[0:i] sum equals k
            else if (m.count(sum - k)) // subarray[j:i] sum equals k
                res = max(res, i - m[sum - k]);
            
            // to max subarray
            // add m[sum] only if no existed
            if (!m.count(sum)) m[sum] = i;
        }
        return res;
    }
};