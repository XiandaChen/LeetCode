class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> res;
        
        if (n & 1) { // odd number
            res.push_back(0);
            n--;
        }
        
        int x = 1;
        while (n > 0) { // even number, add (x,-x) each time
            res.push_back(x);
            res.push_back(-x);
            
            n -= 2;
            x++;
        }
        
        return res;
    }
};