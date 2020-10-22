class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return helper(nestedList, 1);
    }
    int helper(vector<NestedInteger>& nestedList, int depth) {
        int res = 0;
        for (auto a : nestedList) {
            res += a.isInteger() ? a.getInteger() * depth :helper(a.getList(), depth + 1);
        }
        return res;
    }
};

class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        int res = 0;
        vector<int> v; // sum of all integers at each depth
        for (auto a : nestedList) {
            helper(a, 0, v);
        }
        for (int i = (int)v.size() - 1; i >= 0; --i) {
            res += v[i] * ((int)v.size() - i); // reverse depth
        }
        return res;
    }
    void helper(NestedInteger& ni, int depth, vector<int> &v) {
        if (depth >= v.size()) v.resize(depth + 1);
        if (ni.isInteger()) {
            v[depth] += ni.getInteger();
        }
        else {
            for (auto a : ni.getList()) helper(a, depth + 1, v);
        }
    }
};