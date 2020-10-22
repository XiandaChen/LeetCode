class Solution {
public:
    int maximumSwap(int num) { // O(N)
        string s = to_string(num);
        vector<int> lastPos(10, 0); // last occur position of a digit
        for (int i = 0; i < (int)s.size(); ++i)
            lastPos[s[i] - '0'] = i;
        for (int i = 0; i < (int)s.size(); ++i) {
            for (int j = 9; j > s[i] - '0'; --j) { // check if a value larger than s[i] after i 
                if (lastPos[j] > i) {
                    swap(s[i], s[lastPos[j]]);
                    return stoi(s);
                }
            }
        }
        return num;
    }
};
