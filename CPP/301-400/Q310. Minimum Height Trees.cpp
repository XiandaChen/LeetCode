class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        unordered_map<int, set<int>> graph; // edges: node-connectedNodes
        vector<int> degrees(n, 0);
        queue<int> sources; // nodes of degree 1
        set<int> nodes; // all nodes 0-(n-1)
        
        for (auto edge : edges) {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
            degrees[edge[0]]++;
            degrees[edge[1]]++;
        }
        
        for (int i = 0; i < n; i++) {
            nodes.insert(i);
            if (degrees[i] == 1) sources.push(i);
        }
        
        while (!sources.empty()) {
            if (nodes.size() <= 2) break; // remaining only one or two nodes
            
            // peel it layer by layer
            for (int i = sources.size(); i > 0; i--) {
                int t = sources.front(); sources.pop(); // current node of degree 1, called node-1
                nodes.erase(t); // update remaining nodes after removing the leafe node t

                for (int child : graph[t]) { // nodes connected to node-1, called parent-1
                    graph[child].erase(child); // remove node-1 from parent-1's connectedNodes
                    if (--degrees[child] == 1) sources.push(child); // parent-1 has 1 degree
                }                
            }
        }
        
        return vector<int> (nodes.begin(), nodes.end());
    }
};