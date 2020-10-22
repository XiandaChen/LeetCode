class Solution {
public:
    vector<string> UNDER20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                            "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
                            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> UNDER100 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", 
                               "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> HTMB = {"Hundred" ,"Thousand", "Million", "Billion"};
    vector<int> NUMBER = {100, 1000, 1000*1000, 1000*1000*1000};  // process 3 digits
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return convert(num).substr(1); // remove first " "
    }
    string convert(int num) {
        if (num == 0) return "";
        else if (num < 20) return string(" ") + UNDER20[num];
        else if (num < 100) return string(" ") + UNDER100[num / 10] + convert(num % 10);
        else {
            for (int i = 3; i >= 0; --i) {
                if (num >= NUMBER[i]) 
                    return convert(num / NUMBER[i]) + " " + HTMB[i] + convert(num % NUMBER[i]);
            }
        }
        return "";
    }
};