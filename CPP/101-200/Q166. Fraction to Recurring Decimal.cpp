class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        // if (denomiator == 0) {throw "Division by zero";}
        unordered_map<long, int> m; // remainder-pos
        int s1 = numerator >= 0 ? 1 : -1;
        int s2 = denominator >= 0 ? 1 : -1;
        long num = labs(numerator), den = labs(denominator);
        long quo = num / den, rem = num % den;
        string res = to_string(quo);
        if (s1 * s2 == -1 && (quo > 0 || rem > 0)) res = "-" + res;
        if (rem == 0) return res;
        // process the fration
        res += ".";
        string s = ""; int pos = 0;
        while (rem != 0) {
            if (m.count(rem)) {
                s.insert(m[rem], "(");
                s += ")";
                return res + s;
            }
            m[rem] = pos;
            s += to_string((rem * 10) / den);
            rem = (rem * 10) % den;
            ++pos;
        }
        return res + s;
    }
};