class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";
        int i = a.size() - 1, j = b.size() - 1, carry  = 0;
        while (i >= 0 || j >= 0) {
            int c = (i >= 0) ? a[i--] - '0' : 0;
            int d = (j >= 0) ? b[j--] - '0' : 0;
            int sum = c + d + carry;
            res.insert(res.begin(), '0' + (sum % 2));
            carry = sum / 2;
        }
        return carry ? '1' + res : res;
    }
};