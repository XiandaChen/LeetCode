class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> t = nums;
        sort(t.begin(), t.end());
        int n = nums.size(), i = 0, j = n - 1;
        while (i < n && t[i] == nums[i]) ++i;
        while (j > i && t[j] == nums[j]) --j;  // >i, not >=0
        return j - i + 1;
    }
};