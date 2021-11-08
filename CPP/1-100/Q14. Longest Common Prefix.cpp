class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string res = "";
        for (int i = 0; i < strs[0].size(); i++) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (i >= strs[j].size() || strs[j][i] != c) return res;
            }
            res += c;
        }
        return res;
    }
};

// 38. Count and Say
// 1.     1;	2.     11;		3.     21; 		4.     1211
// 5.     111221 ;		6.     312211;			7.     13112221
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
};n