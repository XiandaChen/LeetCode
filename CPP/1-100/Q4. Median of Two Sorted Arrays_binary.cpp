class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        // Make sure n1 <= n2
        if (len1 > len2) return findMedianSortedArrays(nums2, nums1);
        
        // find the indx at nums1 and nums2 that the value be median 
        int left = 0, right = len1, k = (len1 + len2 + 1) / 2; // median indx at merged array
        while (left < right) {
            int mid1 = left + (right - left) / 2, mid2 = k - mid1;
            if (nums1[mid1] < nums2[mid2 - 1])  // -1
                left = mid1 + 1;
            else right = mid1;
        }
        
        // median of merged array: m[k-1] (if odd size), or (m[k-1] + m[k])/2 (if even size)
        int mid1 = left, mid2 = k - mid1;
        
        // the kth element of two sorted arrays
        int val_k = max(mid1 <= 0 ? INT_MIN : nums1[mid1 - 1],  // -1
                      mid2 <= 0 ? INT_MIN : nums2[mid2 - 1]);   // -1
        
        // merge array have odd size;
        if ((len1 + len2) % 2 == 1)
            return val_k;
        
        // the (k+1)th element 
        int val_k1 = min(mid1 >= len1 ? INT_MAX : nums1[mid1],
                      mid2 >= len2 ? INT_MAX : nums2[mid2]);
        
        // merged array have even size
        return (val_k + val_k1) / 2.0;
    }
};

