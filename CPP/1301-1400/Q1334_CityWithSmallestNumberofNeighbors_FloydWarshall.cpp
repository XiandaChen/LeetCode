class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Floyd-Warshall: shortest path between all pair of nodes
        // dp[u,v] = min(dp[u,v], dp[u,k]+dp[k,v])
        
        // INT_MAX/2: in case of sum overflow
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX / 2)); 
        for (auto e : edges)
            dp[e[0]][e[1]] = dp[e[1]][e[0]] = e[2];
        
        for (int k = 0; k < n; ++k)
            for (int u = 0; u < n; ++u)
                for (int v = 0; v < n; ++v)
                    dp[u][v] = min(dp[u][v], dp[u][k] + dp[k][v]);
        
        int res = -1, min_nb = INT_MAX;
        for (int u = 0; u < n; ++u) {
            int nb = 0;
            for (int v = 0; v < n; ++v) {
                if (v != u && dp[u][v] <= distanceThreshold) ++nb; // v!=u
            }
            if (nb <= min_nb) { // <=: update node id for same distance cities
                min_nb = nb;
                res = u;
            }
        }
        
        return res;
    }
};