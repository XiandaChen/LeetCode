//  two distinct indices i and j in the array 
// such that nums[i] = nums[j] and the absolute difference 
// between i and j is at most k.
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (m.count(nums[i]) && i - m[nums[i]] <= k) return true;
            m[nums[i]] = i;
        }
        return false;
    }
};

//  two distinct indices i and j in the array such that 
// the absolute difference between nums[i] and nums[j] is at most t 
// and the absolute difference between i and j is at most k.
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