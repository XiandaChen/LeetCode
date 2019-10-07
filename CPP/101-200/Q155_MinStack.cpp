class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        minval = INT_MAX;
    }
    
    void push(int x) {
        if (x <= minval) {
            st.push(minval); // push pre_minval
            minval = x; // update minval
        }
        st.push(x);
    }
    
    void pop() {
        int t = st.top(); st.pop();
        if (t == minval) {
            minval = st.top(); // update minval = pre_minval
            st.pop(); // pop pre_minval that duplicated in stack
        }
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minval;
    }
private:
    int minval;
    stack<int> st;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */