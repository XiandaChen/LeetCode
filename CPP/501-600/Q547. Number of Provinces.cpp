class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), res = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                res++;
                helper(isConnected, visited, i);
            }
        }
        return res;
    }
    void helper(vector<vector<int>>& isConnected, vector<bool> & visited, int i) {
        visited[i] = true;
        for (int k = isConnected.size() - 1; k >= 0; k--) {
            if (visited[k] || isConnected[k][i] == 0) continue;
            helper(isConnected, visited, k);
        }
    }
};