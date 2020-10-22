class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() - 1, carry = 0;
        string res = "";
        while (i >= 0 || j >= 0) {
            int valA = (i >= 0) ? a[i--] - '0' : 0;
            int valB = (j >= 0) ? b[j--] - '0' : 0;
            res.insert(res.begin(), (valA + valB + carry) % 2 + '0');
            carry = (valA + valB + carry) / 2;
        }
        return (carry == 1) ? '1' + res : res;
    }
};