class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string num = to_string(N);
        int n = num.size(), j = n;
        // traverse from the last to the second
        for (int i = n - 1; i > 0; --i) { 
            if (num[i - 1] <= num[i]) continue; // continue if monotone increasing
            --num[i - 1]; //num[i-1, i]: high-low decreasing
            j = i;
        }
        for (int i = j; i < n; ++i)
            num[i] = '9'; // convert num[j:n] to '9'
        return stoi(num);
    }
};