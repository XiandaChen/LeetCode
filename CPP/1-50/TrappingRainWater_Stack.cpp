class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, i = 0;
        stack<int> st;
        while (i < height.size()) {
            if (st.empty() || height[i] <= height[st.top()])
                st.push(i++);
            else {
                int t = st.top();
                st.pop();
				// check leftmax bounded bar
                if (st.empty()) continue;
                res += (min(height[i], height[st.top()]) - height[t]) * (i - st.top() - 1);
            }
        }
        return res;
    }
};