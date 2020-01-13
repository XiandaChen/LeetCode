/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        int highest = getHighest(mountainArr, n);
        
        int left = 0, right = highest;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < target) left = mid + 1; // '<'
            else right = mid;
        }
        if (mountainArr.get(left) == target) return left;
        
        left = highest, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) > target) left = mid + 1; // '>'
            else right = mid;
        }
        if (mountainArr.get(left) == target) return left;
        
        return -1;
    }
    int getHighest(MountainArray & mountainArr, int n) {
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};