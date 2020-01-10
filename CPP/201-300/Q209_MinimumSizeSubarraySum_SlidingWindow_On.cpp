class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int left = 0, sum = 0, res = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) { 
            sum += nums[i];
            while (left <= i && sum >= s) { // sliding window, two pointers
                res = min(res, i - left + 1);
                sum -= nums[left++];
            }
        }
        // return res; // error, nums=[1,1] s=3, return INT_MAX
        return res == INT_MAX ? 0 : res;
    }
};