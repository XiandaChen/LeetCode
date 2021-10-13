/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

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