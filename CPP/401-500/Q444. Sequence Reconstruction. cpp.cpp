class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (!org.empty() && seqs.empty()) return false;
        
        int n = org.size();
        for (auto seq : seqs) {
            for (int val : seq) {
                if (val < 1 || val > n) return false;  // NOTE, corner case
            }
        }
        
        unordered_map<int, vector<int>> graph; // parent-children
        unordered_map<int, int> indegrees; 
        queue<int> sources; // zero degree nodes
        vector<int> res;
        
        // construct graph
        for (auto seq : seqs) {
            for (int j = 1; j < seq.size(); j++) {
                graph[seq[j - 1]].push_back(seq[j]);
                indegrees[seq[j]]++;
            }
        }
        
        // zero-degree sources
        for (int val : org) {
            if (indegrees[val] == 0) sources.push(val);
        }
        
        while (!sources.empty()) {
            // NOTE, to get unique sequence
            if (sources.size() > 1) return false;  
            
            int t = sources.front(); sources.pop();
            res.push_back(t);
            
            vector<int> children = graph[t];
            for (int child : children)
                if (--indegrees[child] == 0) sources.push(child);
        }
        
        return res == org;
    }
};
