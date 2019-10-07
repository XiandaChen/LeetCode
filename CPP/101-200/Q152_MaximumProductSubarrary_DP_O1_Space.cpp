class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        int res = nums[0], maxNow = nums[0], minNow = nums[0];
        for (int i = 1; i < (int)nums.size(); ++i) {
            int tmax = maxNow, tmin = minNow;
            maxNow = max(max(tmax * nums[i], tmin * nums[i]), nums[i]);
            minNow = min(min(tmax * nums[i], tmin * nums[i]), nums[i]);
            res = max(res, maxNow);
        }
        return res;
    }
};