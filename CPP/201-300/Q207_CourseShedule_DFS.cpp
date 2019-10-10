class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> grap(numCourses, vector<int>());
        vector<int> visit(numCourses); // 0: no, 1: yes, -1: being conflicted
        for (auto a : prerequisites) 
            grap[a[1]].push_back(a[0]);
        for (int i = 0; i < numCourses; ++i)
            if (!canFinish(grap, visit, i)) return false;
        return true;
    }
    bool canFinish(vector<vector<int>> & grap, vector<int> & visit, int i) {
        if (visit[i] == -1) return false; // being visisted twice in one search
        if (visit[i] == 1) return true;
        visit[i] = -1;
        for (int a : grap[i])
            if (!canFinish(grap, visit, a)) return false;
        visit[i] = 1;
        return true;
    }
};