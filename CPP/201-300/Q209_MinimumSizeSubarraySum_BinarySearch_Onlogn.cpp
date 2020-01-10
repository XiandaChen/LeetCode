class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX, len = nums.size();
        vector<int> sums(len + 1, 0); // sums[i]=nums[0:i-1]
        for (int i = 1; i <= len; ++i) sums[i] = sums[i - 1] + nums[i - 1];
        
        for (int i = 0; i < len; ++i) {
            int left = i + 1, right = len;
            
            // find the right indx such that sums[left]>=sums[i]+s
            // then, subarray of length=(left - i)
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (sums[mid] >= sums[i] + s) right = mid - 1;
                else left = mid + 1;
            }
            
            if (left == len + 1) break;
            res = min(res, left - i);
        }
        
        return res == INT_MAX ? 0 : res;
    }
};