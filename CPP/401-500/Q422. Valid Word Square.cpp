class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        if (words.empty()) return false;

        // NOTE, words[i].size() may be equal to words[j].size() for i!=j
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                // if not symmetric
                if (j >= words.size() || i >= words[j].size()) return false;
                
                if (i != j && words[i][j] != words[j][i]) return false;
            }
        }
        
        return true;
    }
};