class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(), partitionIdx = 0, prevMax = nums[0], curMax = nums[0];
        
        for (int i = 1; i < n; i++) {
            curMax = max(curMax, nums[i]);
            if (nums[i] < prevMax) { // Every element in left must <= in right.
                partitionIdx = i;
                prevMax = curMax;
            }
        }
        
        return partitionIdx + 1;
    }
};