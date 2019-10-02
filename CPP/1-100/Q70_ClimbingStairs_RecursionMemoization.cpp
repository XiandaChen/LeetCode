class Solution {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1); // index: 0, 1,..n
        return climbStairs_DFS(n, memo);
    }
    int climbStairs_DFS(int n, vector<int>& memo) {
        if (n <= 1) return 1;
        if (memo[n] > 0) return memo[n];
        return memo[n] = climbStairs_DFS(n - 1, memo) + climbStairs_DFS(n - 2, memo);
    }
};