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
    Node* inorderSuccessor(Node* node) {
        // inorder successor can be parent, right, or null
        // for node, if having right child => leftmost of right-child
        // if no having right child => firstlarger parent (or grandparent..)
        if (!node) return nullptr;
        Node * res = nullptr;
        if (node->right) {
            res = node->right;
            while (res && res->left) res = res->left;
        }
        else {
            res = node->parent;
            while (res && res->val < node->val) res = res->parent;
        }
        return res;
    }
};