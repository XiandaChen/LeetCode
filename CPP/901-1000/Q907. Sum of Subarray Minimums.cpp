// class Solution {
// public:
//     int sumSubarrayMins(vector<int>& arr) {
//         int n = arr.size(), res = arr[0], Mod = 1e9 + 7; // NOTE, res = arr[0]
//         vector<int> dp(n); // dp[i]: sum of subarray minimus where subarrays end with arr[i]
//         dp[0] = arr[0];
//         for (int i = 1; i < n; i++) {
//             if (arr[i] >= arr[i - 1]) {
//                 dp[i] = dp[i - 1] + arr[i];
//             }
//             else { // [2, 3, 1]=>[[2,3,1], [3,1], [1]]
//                 int j = i - 1;
//                 while (j >= 0 && arr[j] > arr[i]) j--;  // O(N^2), time limited exceeded
//                 dp[i] = (j < 0) ? (i + 1) * arr[i] : (dp[j] + (i - j) * arr[i]);
//             }
//             res = (res + dp[i]) % Mod;
//         }
//         return res;
//     }
// };

class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {  // O(N)
        int res = 0, n = arr.size(), Mod = 1e9 + 7;
        stack<int> st{{-1}}; // monotonic stack, ascending order
        vector<int> dp(n + 1); // dp[i]: sum of subarray minimus where subarrays end with arr[i-1]
        for (int i = 0; i < n; i++) {
            while (st.top() != -1 && arr[i] <= arr[st.top()]) st.pop();
            dp[i + 1] = (dp[st.top() + 1] + (i - st.top()) * arr[i]) % Mod;
            st.push(i);
            res = (res + dp[i + 1]) % Mod;  // NOTE, dp[i+1]
        }
        return res;
    }
};
