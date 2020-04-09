class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1, j = T.size() - 1;
        int cnt_i = 0, cnt_j = 0;
        // while (i >= 0 && j >= 0) { // error, S: "nzp#o#g", T: "b#nzp#o#g"
        while (i >= 0 || j >= 0) {
            while (i >= 0 && (S[i] == '#' || cnt_i > 0)) { // backspace
                S[i--] == '#' ? ++cnt_i : --cnt_i;
            }
            while (j >= 0 && (T[j] == '#' || cnt_j > 0)) {
                T[j--] == '#' ? ++cnt_j : --cnt_j;
            }
            if (i < 0 || j < 0) return i == j; // out of loop
            if (S[i--] != T[j--]) return false;
        }
        return i == j;
    }
};
