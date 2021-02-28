// nearestGreater
// Given an array of integers a, return a new array b using the following guidelines:
// For each index i in b, the value of bᵢ is the index of the aⱼ nearest to aᵢ and is also greater than aᵢ.
// If there are two options for bᵢ, put the leftmost one in bᵢ.
// If there are no options for bᵢ, put -1 in bᵢ.
// For a = [1, 4, 2, 1, 7, 6], the output should be nearestGreater(a) = [1, 4, 1, 2, -1, 4].
    
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

vector<int> nearestGreater(vector<int>& nums) {
    stack<pair<int, int>> st; // num-indx
    vector<int> res;
    
    vector<int> leftGreater;
    for (int i = 0; i < (int)nums.size(); ++i) {
        while (!st.empty() && st.top().first <= nums[i]) st.pop();
        leftGreater.push_back(st.empty() ? -1 : st.top().second);
        st.push({nums[i], i});
    }
    
    while (!st.empty()) st.pop();
    
    vector<int> rightGreater;
    for (int i = nums.size() - 1; i >= 0; --i) {
        while (!st.empty() && st.top().first <= nums[i]) st.pop();
        rightGreater.push_back(st.empty() ? -1 : st.top().second);
        st.push({nums[i], i});
    }
    reverse(rightGreater.begin(), rightGreater.end());
    
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (leftGreater[i] == -1 && rightGreater[i] == -1) res.push_back(-1);
        else if (leftGreater[i] == -1) res.push_back(rightGreater[i]);
        else if (rightGreater[i] == -1) res.push_back(leftGreater[i]);
        else if (i - leftGreater[i] <= rightGreater[i] - 1) res.push_back(leftGreater[i]);
        else res.push_back(rightGreater[i]);
    }
    
    return res;
}


int main() {
    vector<int> nums = {1, 4, 2, 1, 7, 6};

    vector<int> res = nearestGreater(nums);

    for (int val : res) {
        cout << val << " ";
    }
    
    return 0;
}
