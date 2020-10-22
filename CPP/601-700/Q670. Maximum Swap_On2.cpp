class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        int res = num, n = s.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(s[i], s[j]);
                res = max(res, stoi(s));
                swap(s[i], s[j]);
            }
        }
        return res;
    }
};