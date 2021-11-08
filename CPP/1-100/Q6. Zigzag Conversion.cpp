class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        vector<string> vec(numRows);
        int i = 0, n = s.size();
        
        while (i < n) {
            for (int row = 0; row < numRows && i < n; row++) {
                vec[row] += s[i++];
            }
            for (int row = numRows - 2; row >= 1 && i < n; row--) {
                vec[row] += s[i++];
            }
        }
        
        string res = "";
        for (string s : vec) res += s;
        
        return res;
    }
};