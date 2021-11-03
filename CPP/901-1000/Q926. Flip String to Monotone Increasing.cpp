class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size(), res = INT_MAX;
        // cnt1[i]: num flipping 1 to 0 in s[0:i-1] to make monotone increasing
        // cnt2[j]: num flipping 0 to 1 in s[j:n-1] to make monotone increasing
        vector<int> cnt1(n + 1), cnt2(n + 1);
        
        for (int i = 1, j = n - 1; j >= 0; i++, j--) {
            cnt1[i] = cnt1[i - 1] + ((s[i - 1] == '1') ? 1 : 0);
            cnt2[j] = cnt2[j + 1] + ((s[j] == '0') ? 1 : 0);
        }
        // at some pos, (cnt1[i] + cnt2[i]) get minimum flippings
        for (int i = 0; i <= n; i++) res = min(res, cnt1[i] + cnt2[i]);
        
        return res;
    }
};

