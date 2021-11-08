class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) return "1";
        
        string str = countAndSay(n - 1), res = "";
        int len = str.size();
        
        for (int i = 0; i < len; i++) {
            int cnt = 1;
            while (i + 1 < len && str[i] == str[i + 1]) {
                cnt++;
                i++;
            }
            res += to_string(cnt) + str[i];
        }
        
        return res;
    }
};