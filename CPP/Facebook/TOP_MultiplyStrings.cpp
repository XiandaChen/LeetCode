class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        vector<int> val(m + n, 0);
        string res = "";
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int high = i + j, low = i + j + 1;
                int sum = (num1[i] - '0') * (num2[j] - '0') + val[low];
                val[low] = sum % 10;  // remainder
                val[high] += sum / 10; // carry
            }
        }
        for (int v : val) {
            // skip leading zeros
            if (!res.empty() || v != 0) res += v + '0';
        }
        return res.empty() ? "0" : res; // corner: num1="0", num2="0"
    }
};