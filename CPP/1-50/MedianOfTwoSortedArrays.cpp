class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        if (len1 > len2)
            return findMedianSortedArrays(nums2, nums1);
        
        int low = 0, high = len1, halfLen = (len1 + len2 + 1) / 2;
        while (low <= high) {
            int cut1 = (low + high) / 2;
            int cut2 = halfLen - cut1;

            if (cut1 > low && nums1[cut1-1] > nums2[cut2]) {
                high = cut1 - 1;    // move toward left in nums1
            }
            else if (cut1 < high && nums2[cut2-1] > nums1[cut1]) {
                low = cut1 + 1;     // move toward right in nums1
            }
            else {
                int maxLeft1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
                int minRight1 = (cut1 == len1) ? INT_MAX : nums1[cut1];

                int maxLeft2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
                int minRight2 = (cut2 == len2) ? INT_MAX : nums2[cut2];
                
                if ((len1 + len2) % 2 == 1)     // total number is odd
                    return max(maxLeft1, maxLeft2);
                else 
                    return (double) (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2;
            }
        }
        
        return 0;
    }
};