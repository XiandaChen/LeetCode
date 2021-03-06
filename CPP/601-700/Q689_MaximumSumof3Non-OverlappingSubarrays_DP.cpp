class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size(), mx = INT_MIN;
        // sums[i]: sum of subarray [0, i]
        // left[i]: start pos of maximum sum subarray of interval [0, i]
        // left[i]: start pos of maximum sum subarray of interval [i, n -1]
        vector<int> res, sums{0}, left(n, 0), right(n, n - k);
        for (int num : nums) sums.push_back(sums.back() + num);
        // start pos for left subarray
        for (int i = k, total = sums[k] - sums[0]; i < n; ++i) {
            if (sums[i + 1] - sums[i + 1 - k] > total) {
                left[i] = i + 1 - k;
                total = sums[i + 1] - sums[i + 1 - k];
            }
            else { left[i] = left[i - 1]; }
        }
        // start pos for right subarray
        for (int i = n - 1 - k, total = sums[n] - sums[n - k]; i >= 0; --i) {
            if (sums[i + k] - sums[i] >= total) { // mustbe ">=", instead of ">"
                right[i] = i;
                total = sums[i + k] - sums[i];
            }
            else { right[i] = right[i + 1]; }
        }
        // start pos for middle subarray
        for (int i = k; i <= n - 2 * k; ++i) {
            int l = left[i - 1], r = right[i + k];
            int total = (sums[i + k] - sums[i]) + 
                        (sums[l + k] - sums[l]) + (sums[r + k] - sums[r]);
            if (total > mx) {
                mx = total;
                res = {l, i, r};
            }
        }
        return res;
    }
};