class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - k; // "- k"
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (abs(arr[mid] - x) > abs(arr[mid + k] - x)) left = mid + 1;
            else right = mid;
        }
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};