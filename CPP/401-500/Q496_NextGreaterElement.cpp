class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) { // both of unique elements
        unordered_map<int, int> m; // val-idx
        vector<int> res(nums1.size());
        
        for (int i = 0; i < (int)nums2.size(); ++i) m[nums2[i]] = i;
        
        for (int i = 0; i < (int)nums1.size(); ++i) {
            res[i] = -1;
            // the first greater number to its right in nums2
            for (int j = m[nums1[i]] + 1; j < (int)nums2.size(); ++j) {
                if (nums2[j] > nums1[i]) {
                    res[i] = nums2[j]; break;
                }
            }
        }
        
        return res;
    }
};