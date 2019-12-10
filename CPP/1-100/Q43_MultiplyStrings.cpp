class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        vector<int> vals(m + n); // length of multiply val is not larger than m+n
        string res = "";
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int highpos = i + j, lowpos = i + j + 1, sum = mul + vals[lowpos]; // previous vals[lowpos] 
                vals[highpos] += sum / 10; // carry
                vals[lowpos] = sum % 10; // remainder
            }
        }
        // add vals in string from high position to low position
        for (int val : vals) {
            // 'val != 0': skip leading zeros
            if (!res.empty() || val != 0) res.push_back(val + '0');
        }
        // return res; // eror for corner case: input="0"
        return res.empty() ? "0" : res; 
    }
};