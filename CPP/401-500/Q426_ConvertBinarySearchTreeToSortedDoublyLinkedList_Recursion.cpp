/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return NULL;
        Node * pre = NULL, * head = NULL; // head: left-most node; pre: pre-accessed node
        inorderTraversal(root, pre, head);
        head->left = pre;   // doubly-liked list
        pre->right = head;
        return head;
    }
    void inorderTraversal(Node * node, Node *& pre, Node *& head) {
        // binary tree inorder traversal
        if (!node) return;
        inorderTraversal(node->left, pre, head);
        
        if (!head) { // access left-most node
            head = node;
            pre = node;
        }
        else {
            pre->right = node;
            node->left = pre;
            pre = node;
        }
        
        inorderTraversal(node->right, pre, head);
    }
};