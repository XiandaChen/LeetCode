class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        if (nums.empty() || nums.front() > 0 || nums.back() < 0) return {};
        
        for (int i = 0; i < (int)nums.size() - 2; i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i-1]) continue;  // remove duplicate triplets
            
            int j = i + 1, k = (int)nums.size() - 1, twosum = 0 - nums[i];
            while (j < k) {
                if (nums[j] + nums[k] == twosum) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    while(j < k && nums[j] == nums[j+1]) j++;   // remove duplicate triplets
                    while(j < k && nums[k] == nums[k-1]) k--;   // remove duplicate triplets
                    j++;
                    k--;
                }
                else if (nums[j] + nums[k] < twosum) j++;
                else k--;
            }
        }
        return res;
    }
};