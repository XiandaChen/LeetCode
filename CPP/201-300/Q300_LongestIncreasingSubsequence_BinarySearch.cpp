class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> subs;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int left = 0, right = subs.size();
            while (left < right) { // binary search the num in subs larger or equal to nums[i]
                int mid = left + (right - left) / 2;
                if (nums[i] <= subs[mid]) right = mid;
                else left = mid + 1;
            }
            if (right >= subs.size()) subs.push_back(nums[i]); // nums[i] is larger than any num in subs
            else subs[right] = nums[i];
        }
        return subs.size(); // length of LIS, but subs is not exactly an LIS
    }
};