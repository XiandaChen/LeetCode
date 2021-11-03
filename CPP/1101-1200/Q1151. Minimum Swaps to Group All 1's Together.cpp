class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n = data.size();
        
        // step 1: Count how many 1 in the data and set this number as the size of sliding window.
        int window = accumulate(data.begin(), data.end(), 0);
        
        if (window == 0 || window == n) return 0; // not need to swap
        
        // ones: num of ones in subwindow [0, window]
        // step 2: count how many 0 in the sliding window.
        int ones = accumulate(data.begin(), data.begin() + window, 0);
        int zeros = window - ones;
        
        // step 3: Shift the sliding window and choose the sliding window with the minimum 0 count.
        int left = 0, right = window, res = zeros;
        while (right < n) {
            zeros -= !data[left++]; // 
            zeros += !data[right++];
            if (zeros < res) res = zeros;
        }
        
        return res;
    }
};