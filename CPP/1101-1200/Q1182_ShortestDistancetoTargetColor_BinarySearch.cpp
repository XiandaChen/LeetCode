class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<int> res;
        unordered_map<int, vector<int>> m; // color-positions
        for (int i = 0; i < colors.size(); ++i)
            m[colors[i]].push_back(i);
        for (auto query : queries) {
            if (!m.count(query[1])) { // color not exist
                res.push_back(-1); continue;
            }
            int pos = closest(m[query[1]], query[0]); // pos of color(query[1]) closest to query[0]
            res.push_back(abs(pos - query[0])); // distance
        }
        return res;
    }
    int closest (vector<int> & nums, int target) {
        // lower_bound: an iterator pointing a value not less than ‘val’
        // upper_bound: an iterator pointing a value greater than ‘val’
        // nums=[5,5,5,6,6,6,7,7], target=6; lowerpos=3, upperpos=6
        int pos = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        if (pos == 0) return nums[0];
        if (pos == nums.size()) return nums[nums.size() - 1];
        // nums=[4,7,8], target=5, nums[pos]=7, comp(abs(4-5) and abs(7-5))
        if (abs(nums[pos] - target) < abs(nums[pos - 1] - target))
            return nums[pos];
        return nums[pos - 1];
    }
};