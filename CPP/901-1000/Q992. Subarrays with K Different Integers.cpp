class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // (subarrays with at most K distinct num) - (subarrays with at most K-1 distinct num)
        return helper(nums, k) - helper(nums, k - 1);
    }
    // subarrays with at most K distinct num
    int helper(vector<int>& nums, int k) {
        int n = nums.size(), left = 0, res = 0;
        unordered_map<int, int> numCnt; // number-count
        for (int i = 0; i < n; i++) {
            if (numCnt[nums[i]] == 0) k--; // k-- if adding new nums[i] to subarray
            numCnt[nums[i]]++;
            while (k < 0) { // sliding window
                if (--numCnt[nums[left]] == 0) k++;
                left++;
            }
            res += i - left + 1;  // count the valid subarrays
        }
        return res;
    }
};

