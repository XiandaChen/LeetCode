class Solution {
public:
    string removeKdigits(string num, int k) {
        string res = "";  // string works as stack: pop_back
        int n = num.size(), keep = n - k;
        for (char c : num) {
            while (k && res.size() && res.back() > c) { // maintain increasing stack
                // remove the last char in res if it is larger than c
                res.pop_back(); --k;
            }
            res.push_back(c);
        }
        res.resize(keep); // num='12345', k=2, res='12345', res.resize(5-2)='123'
        // remove leading zero ('0200'), if any
        while (res.size() && res[0] == '0') res.erase(res.begin());
        return res.empty() ? "0" : res;
    }
};