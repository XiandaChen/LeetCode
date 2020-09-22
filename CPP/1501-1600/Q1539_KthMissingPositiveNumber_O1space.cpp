// Binary search: Time: O(logn); Space: O(1)
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int left = 0, right = arr.size();
        while (left < right) { // the smallest index l s.t. arr[l] – l + 1 >= k
            int mid = left + (right - left) / 2;
            if (arr[mid] - (mid + 1) >= k) right = mid;
            else left = mid + 1;
        }
        return left + k;
    }
};