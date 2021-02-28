// You can swap the characters at any pair of indices in the given pairs any number of times.
// Return the lexicographically smallest string that s can be changed to after using the swaps.

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vector<int>> graph(n);
        for (auto p : pairs) { // construct the graph
            graph[p[0]].push_back(p[1]);
            graph[p[1]].push_back(p[0]);
        }
        
        vector<int> visited(n, 0);
        string res = s;
        
        for (int i = 0; i < n; ++i) { // graph traversal
            if (visited[i]) continue;
            vector<int> indxs; // reachable indx along a path
            vector<char> chars; // chars on the path

            dfs(graph, visited, i, indxs);
            for (int c : indxs) chars.push_back(s[c]);
            
            sort(indxs.begin(), indxs.end());
            sort(chars.begin(), chars.end());  // lexicographically smallest string
            
            for (int j = 0; j < (int)indxs.size(); ++j) {
                res[indxs[j]] = chars[j];  // lexicographically smallest string
				// res[indxs[j]] = chars[indxs.size() - 1 - j];  // lexicographically largest string
            }
        }
        
        return res;
    }
    
    void dfs(vector<vector<int>>& graph, vector<int>& visited, int cur, 
             vector<int>& indxs) {
        if (visited[cur]) return;
        visited[cur] = 1;
        indxs.push_back(cur);
        for (auto child : graph[cur]) {
            if (!visited[child]) dfs(graph, visited, child, indxs);
        }
    }
};
