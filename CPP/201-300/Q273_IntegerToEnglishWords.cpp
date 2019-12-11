class Solution {
public:
    string numberToWords(int num) {
        vector<string> v = {"Thousand", "Million", "Billion"};
        string res = process3digit(num % 1000); // process the last three digit
        for (int i = 0; i < 3; ++i) { // INT_MAX: billion, three more 3-digit parts
            num /= 1000; // remove last three digit
            res = num % 1000 ? process3digit(num % 1000) + " " + v[i] + " " + res : res;
        }
        // remove spaces at the end
        while (res.back() == ' ') res.pop_back();
        // check zero
        return res.empty() ? "Zero" : res;
    }
    string process3digit(int num) { // helper func to process less-than thousand
        vector<string> v1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                            "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
                            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        vector<string> v2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        string res;
        int a = num / 100, b = num % 100, c = num % 10; // a: hundreds, b:tens, c: ones
        // get from v1 if less than twenty, otherwise we need v2
        res = b < 20 ? v1[b] : v2[b / 10] + (c ? " " + v1[c] : ""); // for >= 20, check c
        if (a > 0)
            res = v1[a] + " Hundred" + (b ? " " + res : ""); // check b
        return res;
    }
};