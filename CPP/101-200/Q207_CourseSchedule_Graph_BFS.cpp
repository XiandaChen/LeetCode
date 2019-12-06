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