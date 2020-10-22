class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        // multiset: ascending sort by default, allow duplicates
        multiset<int, greater<int>> ms; // descending order
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i >= k) ms.erase(ms.find(nums[i - k])); // ms.erase(nums[i-k]) will erase all duplicates
            ms.insert(nums[i]);
            if (i >= k -1) res.push_back(*ms.begin());
        }
        return res;
    }
};