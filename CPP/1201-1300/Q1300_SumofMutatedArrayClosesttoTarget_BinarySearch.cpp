class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        // // n * log(M), M=max(arr)
        int left = 0, right = * max_element(arr.begin(), arr.end()); // #include <algorithm>
        while (left < right) {
            int mid = left + (right - left) / 2;
            // sum less than target, increase the value
            if (sum(arr, mid) < target) 
                left = mid + 1;
            else right = mid;
        }
        // '<=': In case of a tie, return the minimum such integer.
        if (abs(sum(arr, left - 1) - target) <= abs(sum(arr, left) - target))
            return left - 1;
        return left;
    }
    int sum (vector<int>& arr, int val) {
        int sum = 0;
        for (int x : arr) 
            sum += min(x, val);
        return sum;
    }
};

