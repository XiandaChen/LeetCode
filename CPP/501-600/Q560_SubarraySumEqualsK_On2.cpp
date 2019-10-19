class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size(), res = 0;
        vector<int> sum = nums;
        for (int i = 1; i < n; ++i)
            sum[i] = sum[i - 1] + nums[i];
        for (int i = 0; i < n; ++i) {
            if (sum[i] == k) ++ res;
            for (int j = i - 1; j >= 0; --j)
                if (sum[i] - sum[j] == k) ++ res;
        }
        return res;
    }
};