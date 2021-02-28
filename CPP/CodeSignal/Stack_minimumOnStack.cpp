// Implement a modified stack that, in addition to using push and pop operations, 
// allows you to find the current minimum element in the stack by using a min operation.            

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

vector<int> minimumOnStack(vector<string>& operations) {
    stack<int> st;
    vector<int> res;
    for (string operation : operations) {
        stringstream ss(operation);
        string op; ss >> op;
        if (op == "min") {
            res.push_back(st.top());
        }
        else if (op == "push") {
            int val; ss >> val;
            if (st.empty())
                st.push(val);
            else 
                st.push(min(st.top(), val));
        }
        else {
            st.pop();
        }
    }
    return res;
}

int main() {
    vector<string> operations = {"push 10", "min", "push 5", "min", "push 8", "min", "pop", "min", "pop", "min"};

    vector<int> res = minimumOnStack(operations);

    for (int sum : res) {
        cout << sum << " ";
    }
    
    return 0;
}
