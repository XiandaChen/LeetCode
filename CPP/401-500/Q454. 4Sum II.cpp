class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> m; // complement fo 2sum - count
        int res = 0;
        
        for (int i = (int)nums1.size() - 1; i >= 0; i--) {
            for (int j = (int)nums2.size() - 1; j >= 0; j--) {
                m[nums1[i] + nums2[j]]++;
            }
        }
        
        for (int i = (int)nums3.size() - 1; i >= 0; i--) {
            for (int j = (int)nums4.size() - 1; j >= 0; j--) {
                int target = -1 * (nums3[i] + nums4[j]);
                res += m[target];
            }
        }
        
        return res;
    }
};