class Solution {
public:
    string removeDuplicates(string s) {
        string res = s;
        int len = res.size();
        
        for (int i = 0; i < len; ) {
            int j = i, k = 2; // k=2: remove two adjacent duplicates
            
            while (--k > 0 && j + 1 < len && res[i] == res[j + 1]) j++;
            
            // there is adjacent duplicates
            if (j - i > 0) {
                // string& erase (size_t pos = 0, size_t len = npos);
                res.erase(i, j - i + 1);
                
                // update idx i, // pull back one char
                i = (--i) < 0 ? 0 : i;

                // update string len after removal
                len = res.size();
            }
            else {
                // no duplicate, move i forward
                i++;
            }

        }
            
        return res;
    }
};