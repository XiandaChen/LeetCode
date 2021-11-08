// 207. Course Schedule
// BFS
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses, vector<int>()); // 
        vector<int> indegree(numCourses); // indegree = num of pre for a course
        queue<int> q; // hold indegree=0 node to start graph traversal
        // constructure graph
        for (auto a : prerequisites) {
            graph[a[1]].push_back(a[0]); // course_i -- coursesNeedPre_i
            ++indegree[a[0]];
        }
        // zero-indegree node
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) q.push(i);
        }
        // BFS graph traversal
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (auto a : graph[t]) { // all courses require t as pre
                --indegree[a];
                if (indegree[a] == 0) q.push(a);
            }
        }
        // check if all course satisfy it pre
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i]) return false;
        }
        return true;
    }
};

// 269. Alien Dictionary
// Derive the order of letters in an alien language.
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_set<char> chars; // store all chars in given words
        set<pair<char, char>> st; // store order pairs
        vector<int> indegree(128); // here assume first 128 ASCII
        queue<char> q; // to hold zero-indegree node, and BFS traverse the graph
        string res;
        
        for (string w : words) chars.insert(w.begin(), w.end()); // get all chars in given words
        for (int i = 0; i < words.size() - 1; ++i) { // find all order pairs
            int mn = min(words[i].size(), words[i + 1].size());
            for (int j = 0; j < mn; ++j) {
                if (words[i][j] != words[i + 1][j]) { // diff chars b/w two near words
                    st.insert(make_pair(words[i][j], words[i + 1][j]));
                    break; // dont forget
                }
            }
        }
        for (auto a : st) ++indegree[a.second]; // indegree for chars
        for (auto ch : chars) { // add chars of indegree=zero to queue, that is traversed first
            if (indegree[ch] == 0) {
                q.push(ch);
                res.push_back(ch);
            }
        }
        while (!q.empty()) { // BFS traverse the graph from zero-indegree char
            char ch = q.front(); q.pop();
            for (auto a : st) { // check if ch is in the set st
                if (ch == a.first) {
                    --indegree[a.second];
                    if (indegree[a.second] == 0) {
                        q.push(a.second);
                        res.push_back(a.second);
                    }
                }
            }
        }
        return res.size() == chars.size() ? res : "";
    }
};

//953. Verifying an Alien Dictionary
// Check if the given words are sorted lexicographicaly in the alien language.
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> dic;
        for (int i = 0; i < order.size(); ++i) dic[order[i]] = i; // alien dict order
        for (int i = 1; i < words.size(); ++i) {
            int l1 = words[i - 1].size(), l2 = words[i].size(), j = 0;
            for (; j < min(l1, l2); ++j) {
                if (dic[words[i - 1][j]] < dic[words[i][j]]) break; // if first-ch smaller
                else if (dic[words[i - 1][j]] > dic[words[i][j]]) return false;
            }
            if (j == min(l1, l2) && l1 > l2) return false; // check input: ["apple","app"]
        }
        return true;
    }
};

// 785. Is Graph Bipartite?  
// BFS, queue 
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
// DFS
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

// 133. Clone Graph
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        unordered_map<Node*, Node*> m; // orignode-clonenode
        Node * clone = new Node(node->val);
        m[node] = clone;
        queue<Node*> q{{node}}; // BFS graph traversal
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                for (auto neighbor : t->neighbors) {
                    if (!m.count(neighbor)) {
                        m[neighbor] = new Node(neighbor->val); // clone neighbor
                        q.push(neighbor); // add orig neighbor to queue
                    }
                    //add neighbor of cloned node
					// vector<Node*> neighbors;
                    m[t]->neighbors.push_back(m[neighbor]);
                }
            }
        }
        return clone;
    }
};

// 200. Number of Islands, DFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n)); 
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // skip if grid[i][j]=0, or had been visited
                if (grid[i][j] == '0' || visited[i][j]) continue;
                dfs(grid, i, j, visited);
                ++res;
            }
        }
        return res;
    }
    void dfs(vector<vector<char>> & grid, int i, int j, vector<vector<bool>> & visited) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() 
           || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(grid, i + 1, j, visited);
        dfs(grid, i - 1, j, visited);
        dfs(grid, i, j + 1, visited);
        dfs(grid, i, j - 1, visited);
    }
};

// Shortest path in Graph (negative cycle not allowed)
// Dijkstra: one node to all nodes, negative edge not allowed
//		time: O(VElogV), space: O(V+E)
// Bellman-Ford: one node to all nodes, negative edge allowed
// Floyd-Warshall: all pairs of nodes, negative edge allowed 
//		for k,i,j: dp[i,j] = min(dp[i,j], dp[i,k]+dp[k,j])
//		time: O(V^3), space: O(V^2)
// 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
// If there are multiple such cities, return the city with the greatest number.
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




