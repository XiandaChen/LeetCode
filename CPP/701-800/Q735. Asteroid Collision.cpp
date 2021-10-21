class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        vector<int> res;
        
        for (int a : asteroids) {
            if (st.empty() || a > 0 ) {
                st.push(a);
            }
            else {
                while (!st.empty() && 0 < st.top() && st.top() < abs(a)) st.pop();
                
                if (!st.empty() && st.top() == abs(a)) {
                    st.pop(); // both explode
                }
                else if (st.empty() || st.top() < 0) {
                    st.push(a);
                }
            }
        }
        
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};