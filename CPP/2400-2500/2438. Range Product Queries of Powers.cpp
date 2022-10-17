class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        // 110101 = 2^0 + 2^2 + 2^4 + 2^5
        // 2^x + 2^y = 2^(x+y)
        vector<int> exp;
        for (int i = 0; i < 32; i++) {
            if (n%2 == 1) exp.push_back(i);
            n /= 2;
            if (n == 0) break;
        }
        
        vector<int> presum(exp.size());
        presum[0] = exp[0];
        for (int i = 1; i < exp.size(); i++) {
            presum[i] = presum[i - 1] + exp[i];
        }
        
        vector<long> twos(32 * 32, 1);
        long M = 1e9 + 7;
        for (int i = 1; i < 32 * 32; i++) {
            twos[i] = twos[i - 1] * 2 % M;
        }
        
        vector<int> ret;
        for (auto & query: queries) {
            int l = query[0], r = query[1];
            int sum = presum[r] - (l == 0 ? 0 : presum[l - 1]);
            //runtime error: 2.14748e+09 is outside the range of int
            // ret.push_back(int(pow(2, sum)) % M); 
            ret.push_back(twos[sum]);
        }
        
        return ret;
    }
};