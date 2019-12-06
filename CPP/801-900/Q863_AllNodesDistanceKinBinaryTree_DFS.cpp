/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root) return {};
        vector<int> res;
        unordered_map<TreeNode*, TreeNode*> parent; // node's parent
        unordered_set<TreeNode*> visited; // to hold visited nodes
        findParent(root, parent);
        helper(target, K, parent, visited, res);
        return res;
    }
    void findParent(TreeNode * node, unordered_map<TreeNode*, TreeNode*> & parent) {
        if (!node) return;
        if (node->left) {
            parent[node->left] = node;
            findParent(node->left, parent);
        }
        if (node->right) {
            parent[node->right] = node;
            findParent(node->right, parent);
        }
    }
    void helper(TreeNode * node, int K, unordered_map<TreeNode*, TreeNode*> & parent, 
               unordered_set<TreeNode*> & visited, vector<int> & res) {
        if (!node || visited.count(node)) return; // if node is null, or had been visited
        visited.insert(node);   // been visited
        if (K == 0) {res.push_back(node->val); return;}
        if (node->left) helper(node->left, K - 1 , parent, visited, res); // left
        if (node->right) helper(node->right, K - 1, parent, visited, res); // right
        if (parent[node]) helper(parent[node], K - 1, parent, visited, res); // parent
    }
};