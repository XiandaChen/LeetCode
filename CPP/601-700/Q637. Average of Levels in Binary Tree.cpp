class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if (!root) return {};
        vector<double> res;
        queue<TreeNode *> q{{root}};
        while (!q.empty()) {
            int n = q.size();
            double sum = 0;
            for (int i = n; i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                sum += t->val;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(sum / n);
        }
        return res;
    }
};