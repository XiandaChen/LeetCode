class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[2] < b[2];
        };
        sort(connections.begin(), connections.end(), cmp);
        
        vector<int> parent(n + 1, 0); // n cities labeled from 1 to n
        for (int i = 1; i <= n; i++) parent[i] = i;
        
        int numVisited = 1, res = 0;  // NOTE, numVisited==1
        
        for (auto & c : connections) {
            int x = find(parent, c[0]), y = find(parent, c[1]);
            if (x != y) { // if x==y: node x and y belong to same group
                res += c[2];
                numVisited++;
                parent[x] = y;
            }
            if (numVisited == n) return res;
        }
        return -1;
    }
    
    int find(vector<int> & parent,  int i) { // union find
        if (parent[i] != i) parent[i] = find(parent, parent[i]);
        return parent[i];
    }
};