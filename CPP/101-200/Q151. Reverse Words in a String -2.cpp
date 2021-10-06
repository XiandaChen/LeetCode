class Solution {
public:
    string reverseWords(string s) {
        int n = s.size(), idx = 0;
        reverse(s.begin(), s.end());
        
        for (int i = 0; i < n; i++) {
            if (s[i] != ' ') {
                if (idx != 0) s[idx++] = ' '; // add ' ' before new word
            
                int j = i; 
                while (j < n && s[j] != ' ') s[idx++] = s[j++];

                // reverse the word
                reverse(s.begin() + idx - (j - i), s.begin() + idx);

                i = j; // for next word
            }
        }
        s.resize(idx);
        return s;
    }
};