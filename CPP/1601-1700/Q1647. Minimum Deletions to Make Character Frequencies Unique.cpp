class Solution {
public:
    int minDeletions(string s) {
        unordered_map<char, int> m; // char-freq
        vector<int> freq;  
        set<int> fset; // freq set after deletion
        int res = 0;
        
        for (char c : s) m[c]++;
        
        for (auto a : m) freq.push_back(a.second);
        sort(freq.begin(), freq.end()); // sort frequency
        
        for (int i = freq.size() - 1; i >= 0; i--) { // search from largest freq
            if (!fset.count(freq[i])) {
                fset.insert(freq[i]);
            }
            else { // freq[i] already exists, then deletion
                int k = freq[i] - 1;
                while (k > 0 && fset.count(k)) k--;
                
                if (k > 0) fset.insert(k);
                
                res += freq[i] - k; // add deletions
            }
        }
        
        return res;
    }
};