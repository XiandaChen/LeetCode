class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        helper(num, target, 0, 0, "", res);
        return res;
    }
    void helper(string numstr, int target, long value, int pre_num, 
                string equation, vector<string> & res) {
        // iterate to the end of given num, and value equals to target
        if (numstr.size() == 0 && value == target) {
            res.push_back(equation); return;
        }
        //
        for (int i = 1; i <= numstr.size(); ++i) { // "i=1" and "<=", as for substr()
            string cur = numstr.substr(0, i); // substr as a num
            string next = numstr.substr(i); // add operator b/w cur and next
            
            if (cur.size() > 1 && cur[0] == '0') return; // num not start with zero
            
            if (equation.size() == 0) { // initialize equation with cur substr in the front
                helper(next, target, stoll(cur), stoll(cur), cur, res);
                continue;
            }
            
            // For "*", it needs trace back the pre_number
            helper(next, target, value + stoll(cur), stoll(cur), equation + "+" + cur, res);
            helper(next, target, value - stoll(cur), -stoll(cur), equation + "-" + cur, res);
            helper(next, target, value - pre_num + pre_num * stoll(cur), pre_num * stoll(cur), 
                   equation + "*" + cur, res);
        }
    }
};