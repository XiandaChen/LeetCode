class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0, minDiff = INT_MAX;
        for (int i = 0; i < n - 2; ++i) {  // 'n - 2'
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                int curdiff = abs(target - cursum);
                if (curdiff < minDiff) {
                    res = cursum;
                    minDiff = curdiff;
                }
                if (cursum < target) ++left;
                else --right;
            }
        }
        return res;
    }
};