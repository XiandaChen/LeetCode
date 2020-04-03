class Solution {
public:
    bool isHappy(int n) {
        if (n < 0) return false;
        string num = to_string(n);
        int sum = 0;
        for (int i = 0; i < size(num); ++i)
            sum += pow(num[i] - '0', 2);
        if (sum == 1) return true;
        return !st.count(sum) && isHappy(sum);
    }
private:
    unordered_set<int> st;
};