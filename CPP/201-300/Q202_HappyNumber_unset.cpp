class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> st;
        
        while (n != 1) {
            string num = to_string(n);
            int sum = 0;
            for (int i = 0; i < size(num); ++i)
                sum += pow(num[i] - '0', 2);
            if (st.count(sum)) break;
            else st.insert(sum);
            n = sum;
        }
        
        return n == 1;
    }
};