class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        if (accounts.empty()) return {};
        vector<vector<string>> res;
        unordered_map<string, string> emailToName; // email-name
        unordered_map<string, set<string>> graph; // email-neighbors
        set<string> emails; // all emails
        set<string> visited; // for dfs
        // build the graph
        for (auto acc : accounts) {
            string name = acc[0];
            for (int i = 1; i < (int)acc.size(); ++i) {
                string email = acc[i];
                emails.insert(email);
                emailToName[email] = name;
                if (i == 1) continue;
                graph[acc[i]].insert(acc[i - 1]);
                graph[acc[i - 1]].insert(acc[i]);
            }
        }
        // main func
        for (auto email : emails) {
            if (!visited.count(email)) { // not checked yet
                visited.insert(email);
                vector<string> out {{email}};
                dfs(graph, visited, email, out);
                sort(out.begin(), out.end());
                out.insert(out.begin(), emailToName[email]);
                res.push_back(out);
            }
        }
        return res;
    }
    // dfs to add all connnected emails to a name
    void dfs(unordered_map<string, set<string>>& graph, set<string>& visited, 
            string email, vector<string>& out) {
        for (auto neigh : graph[email]) {
            if (!visited.count(neigh)) {
                visited.insert(neigh);
                out.push_back(neigh);
                dfs(graph, visited, neigh, out);
            }
        }
    }
};