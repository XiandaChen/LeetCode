class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size()); // 0: not accessed, -1/1: diff colors
        for (int i = 0; i < graph.size(); ++i) { // traverse all nodes
            if (colors[i] != 0) continue; // had been colored
            colors[i] = 1; // color 1
            queue<int> q{{i}}; // neighbors
            while (!q.empty()) {
                int t = q.front(); q.pop();
                for (auto a : graph[t]) {
                    if (colors[a] == colors[t]) return false; // node of an edge have same color
                    if (colors[a] == 0) { // node a have not been colored
                        colors[a] = -1 * colors[t]; // diff color
                        q.push(a); // BFS queue
                    }
                }
            }
        }
        return true;
    }
};