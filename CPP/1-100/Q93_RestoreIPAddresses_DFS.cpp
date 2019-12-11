class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        restore(s, 4, "", res); // k=4: still need 4 partition
        return res;
    }
    void restore(string s, int k, string out, vector<string> & res) {
        if (k == 0) { // we have 4 parts
            if (s.size() == 0) res.push_back(out);
        }
        else { // partition s 
            for (int i = 1; i <= 3; ++i) {
                if (s.size() >= i && isValid(s.substr(0, i))) {
                    if (k == 1) // last partition
                        restore(s.substr(i), k - 1, out + s.substr(0, i), res);
                    else // not the last partition
                        restore(s.substr(i), k - 1, out + s.substr(0, i) + '.', res);
                }
            }
        }
    }
    bool isValid(string s) {
        // IP add part has size 1-3
        if (s.empty() || s.size() > 3 || (s.size() > 1 && s[0] == '0')) return false;
        int val = atoi(s.c_str()); // c_str() pointer of an array(string)
        return 0 <= val && val <= 255;
    }
};