class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size(), zeros = 0, ones= 0, res = 0;
        
        if (s[0] == '0') zeros++;
        else ones++;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == '0') {
                zeros = (s[i - 1] == '0') ? zeros + 1 : 1;
                if (ones >= zeros) res++;
            }
            else if (s[i] == '1') {
                ones = (s[i - 1] == '1') ? ones + 1 : 1;
                if (zeros >= ones) res++;
            }
        }
        
        return res;
    }
};