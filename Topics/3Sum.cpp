// 15. 3Sum
// Input: nums = [-1,0,1,2,-1,-4]; Output: [[-1,-1,2],[-1,0,1]]
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        if (nums.empty() || nums[0] > 0 || nums[nums.size() - 1] < 0) return {};
        vector<vector<int>> res;
        for (int i = 0; i < (int)nums.size() - 2; ++i) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue; // trim off duplicates
            int j = i + 1, k = nums.size() - 1, twosum = 0 - nums[i];
            while (j < k) {
                if (nums[j] + nums[k] == twosum) {
                    res.push_back({nums[i], nums[j], nums[k]});
                    while (j < k && nums[j] == nums[j + 1]) ++j; // trim off duplicates
                    while (j < k && nums[k] == nums[k - 1]) --k;
                    ++j; --k;
                }
                else if (nums[j] + nums[k] < twosum) ++j;
                else --k;
            }
        }
        return res;
    }
};

// 259. 3Sum Smaller
// Input: nums = [-2,0,1,3], target = 2; Output: 2
// Explanation: [-2,0,1]; [-2,0,3]
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0;
        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                if (cursum < target) {
                    res += right - left;
                    ++left;
                }
                else --right;
            }
        }
        return res;
    }
};

// 16. 3Sum Closest
// Input: nums = [-1,2,1,-4], target = 1; Output: 2
// Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), res = 0, minDiff = INT_MAX;
        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1, right = n - 1;
            while (left < right) {
                int cursum = nums[i] + nums[left] + nums[right];
                int curdiff = abs(target - cursum);
                if (curdiff < minDiff) {
                    res = cursum;
                    minDiff = curdiff;
                }
                if (cursum < target) ++left;
                else --right;
            }
        }
        return res;
    }
};
