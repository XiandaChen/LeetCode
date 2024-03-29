class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), cur = 0;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && chars[j] == chars[i]) j++;
            
            chars[cur++] = chars[i]; // write in-place
            
            // only one char, not need to add cnt
            if (j - i == 1) continue; 
            
            // for repeating char, add cnt
            for (char c : to_string(j - i)) chars[cur++] = c;
        }
        return cur;
    }
};