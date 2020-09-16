class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0;
        for (int i = 0; i < n - 2; ++i) { // n - 2
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                if (cursum < target) {
                    res += right - left; // not: res += 1;
                    ++left;
                }
                else --right;
            }
        }
        return res;
    }
};