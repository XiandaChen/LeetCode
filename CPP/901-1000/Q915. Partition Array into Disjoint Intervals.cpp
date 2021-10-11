class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(), maxLeft = INT_MIN;
        vector<int> minRight(n);
        
        minRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = min(nums[i], minRight[i + 1]);
        }
        
        for (int i = 0; i < n - 1; i++) { // NOTE, n-1, i.e., left and right are non-empty
            maxLeft = max(maxLeft, nums[i]);
            if (maxLeft <= minRight[i + 1]) return i + 1;
        }
        
        return 0;
    }
};