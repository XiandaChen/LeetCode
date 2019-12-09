class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size()); // 0: not accessed, -1/1: diff colors
        for (int i = 0; i < graph.size(); ++i) { // traverse all nodes
            if (colors[i] == 0 && !valid(graph, colors, i, 1)) return false;
        }
        return true;
    }
    bool valid(vector<vector<int>>& graph, vector<int> & colors, int cur, int color) {
        if (colors[cur] != 0) return colors[cur] == color; // node cur had been colored, with valid color
        colors[cur] = color;
        for (auto a : graph[cur]) {
            if (!valid(graph, colors, a, -1 * color)) return false;
        }
        return true;
    }
};