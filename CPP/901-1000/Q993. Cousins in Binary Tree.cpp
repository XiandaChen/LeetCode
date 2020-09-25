class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if (!root || (!root->left && !root->right)) return false;
        queue<TreeNode *> q{{root}};
        while (!q.empty()) {
            bool foundFirst = false;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * cur = q.front(); q.pop();
                
                if (cur->left && (cur->left->val == x || cur->left->val == y)) {
                    if (!foundFirst) foundFirst = true;
                    else return true;
                }
                else if (cur->right && (cur->right->val == x || cur->right->val == y)) {
                    if (!foundFirst) foundFirst = true;
                    else return true;
                }
                
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
        }
        return false;
    }
};
