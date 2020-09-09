class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        if (nums.empty() || nums.front() > 0 || nums.back() < 0) return {};
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;  // j > i+1
                int left = j + 1, right = n - 1;
                while (left < right) {
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left + 1] == nums[left]) ++left;
                        while (left < right && nums[right - 1] == nums[right]) --right;
                        ++left; --right;
                    }
                    else if (sum < target) ++left;
                    else --right;
                }
            }
        }
        return res;
    }
};