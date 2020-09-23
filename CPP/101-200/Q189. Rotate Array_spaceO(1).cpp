class Solution {
public:
    void rotate(vector<int>& nums, int k) { 
        if (nums.empty() || (k %= nums.size()) == 0) return;
        int n = nums.size();                        // 1 2 3 4 5 6 7
        reverse(nums.begin(), nums.begin() + n - k); // 4 3 2 1 5 6 7
        reverse(nums.begin() + n - k, nums.end());  // 4 3 2 1 7 6 5
        reverse(nums.begin(), nums.end());          // 5 6 7 1 2 3 4
    }
};