// 235. Lowest Common Ancestor of a Binary Search Tree
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        if (root->val > p->val && root->val > q->val) 
            return lowestCommonAncestor(root->left, p, q);
        
        if (root->val < p->val && root->val < q->val)
            return lowestCommonAncestor(root->right, p, q);
        
        return root;
    }
};
// 236. Lowest Common Ancestor of a Binary Tree
// TreeNode *p and *q exist in the tree
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root; // one of p/q to be ancestor of the other
        
        TreeNode * left = lowestCommonAncestor(root->left, p, q);
        TreeNode * right = lowestCommonAncestor(root->right, p, q);
        
        // if p and q exist at two diff sides, root is the ancestor
        if (left && right) return root;
        
        return (left) ? left : right;
    }
};
// 1644. Lowest Common Ancestor of a Binary Tree II
// If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (checkIfExists(root, p) && checkIfExists(root, q))
            return lca(root, p, q);
        else
            return NULL;
    }
    
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root; // one of p/q to be ancestor of the other
        
        TreeNode * left = lca(root->left, p, q);
        TreeNode * right = lca(root->right, p, q);
        
        // if p and q exist at two diff sides, root is the ancestor
        if (left && right) return root;
        
        return (left) ? left : right;
    }
    
    bool checkIfExists(TreeNode* root, TreeNode* node){
        if(root == NULL || node == NULL)
            return false;
        if(root->val == node->val)
            return true;
        if(checkIfExists(root->left, node) || checkIfExists(root->right, node))
            return true;
        
        return false;
    }
};
// 1650. Lowest Common Ancestor of a Binary Tree III
// Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
// Each node will have a reference to its parent node. 
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        if (p == NULL || q == NULL || p == q) return p;
        
        if (search(p, q)) return p;
        else if (search(q, p)) return q;
        else return lowestCommonAncestor(p->parent, q->parent);
    }
    
    bool search(Node * root, Node * node) { // check if node in root
        if (!root) return false;
        
        if (root == node || search(root->left, node) || search(root->right, node))
            return true;
        else 
            return false;
    }
};
// 1676. Lowest Common Ancestor of a Binary Tree IV
// Given the root of a binary tree and an array of TreeNode objects nodes
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return NULL;
        
        if (nodes.size() == 1) return nodes[0];
        
        for (auto & node : nodes) {
            if (node == root) return root;  // if nodes include root
        }
        
        bool left = search(root->left, nodes);
        bool right = search(root->right, nodes);
        
        if (left && right) { // nodes exist in both left and right sides
            return root;
        }
        else if (left) {
            return lowestCommonAncestor(root->left, nodes);
        }
        else {
            return lowestCommonAncestor(root->right, nodes);
        }
    }
    
    // true: if there is a node in current tree
    bool search(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return false;
        for (auto & node : nodes) {
            if (root->val == node->val) return true;
        }
        return search(root->left, nodes) || search(root->right, nodes);
    }
};


