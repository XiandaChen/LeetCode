// nextLarger, next larger element to its right
// input {11, 13, 21, 3}, output {11, 13, 21, 3}
    
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

vector<int> nextLarger(vector<int>& nums) {
    vector<int> res;
    stack<int> st;
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (st.empty()) res.push_back(-1);
        else {
            while (!st.empty() && st.top() < nums[i]) st.pop();
            res.push_back(st.empty() ? -1 : st.top());
        }
        st.push(nums[i]);
    }
    reverse(res.begin(), res.end());
    return res;
}


int main() {
    vector<int> nums = {11, 13, 21, 3};

    vector<int> res = nextLarger(nums);

    for (int val : res) {
        cout << val << " ";
    }
    
    return 0;
}
