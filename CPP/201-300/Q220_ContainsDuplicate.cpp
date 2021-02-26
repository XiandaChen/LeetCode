class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        map<long, int> m; // ordering map, val-indx
        int j = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i - j > k) m.erase(nums[j++]); // sliding window
            // nums[i] - nums[j] <= t ==> to find (val >= nums[i] - t) in map
            auto a = m.lower_bound((long)nums[i] - t); // larger or equals to
            if (a != m.end() && abs(nums[i] - a->first) <= t) return true;
            m[nums[i]] = i;
        }
        return false;
    }
};