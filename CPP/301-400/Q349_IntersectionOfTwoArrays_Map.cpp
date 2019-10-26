class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty() || nums2.empty()) return {};
        vector<int> res;
        unordered_map<int, int> m;
        for (auto num : nums1) ++m[num];
        for (int i = 0; i < (int)nums2.size(); ++i) {
            //if (m[num].count()) res.push_back(num);
            if (m[nums2[i]]) {
                res.push_back(nums2[i]);
                m[nums2[i]] = 0;
            }
        }
        return res;
    }
};