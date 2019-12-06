class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, n = nums.size();
        vector<int> sums(n); // sums[i]: sum of 0..i
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i) // sums
            sums[i] = sums[i - 1] + nums[i];
        for (int i = 0; i < n; ++i) { // check sums[j..i], j = 0..(i-1)
            if (sums[i] == k) ++res;
            for (int j = i - 1; j >= 0; --j) {
                if (sums[i] - sums[j] == k) ++res;
            }
        }
        return res;
    }
};