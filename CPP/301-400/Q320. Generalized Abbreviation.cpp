class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> res;
        helper(word, 0, 0, "", res);
        return res;
    }
    void helper(string word, int pos, int cnt, string out, vector<string>& res) {
        if (pos == word.size()) {
            if (cnt > 0) out += to_string(cnt);
            res.push_back(out);
        }
        else {
            // abbreviated the char at pos
            helper(word, pos + 1, cnt + 1, out, res);
            // keep the char at pos
            helper(word, pos + 1, 0, out + (cnt > 0 ? to_string(cnt) : "") + word[pos], res);
        }
    }
};