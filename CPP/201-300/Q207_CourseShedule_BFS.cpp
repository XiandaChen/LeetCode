class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> grap(numCourses, vector<int>()); // adjcent list(array)
        vector<int> degree(numCourses); // num of prerequistes of a course (indegree)
        for (auto a : prerequisites) { // construct grap
            grap[a[1]].push_back(a[0]);
            ++degree[a[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
            if (!degree[i]) q.push(i); // start searching from degree=0 course
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (auto a : grap[t]) {
                --degree[a];
                if (degree[a] == 0) q.push(a);
            }
        }
        for (int i = 0; i < numCourses; ++i)
            if (degree[i]) return false;
        return true;
    }
};