#include <iostream>


/*
             50                      
           /     \         
          30      70           
         /  \    /                    
       20   40  60   
       */
// 30 => next (inorder)
// left-most node of the right tree

// time: O(logN)

// ####################### without parent pointer ###############################


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // left/right not exist, root=right/left
            // left & right not exist, root=null
            if (!root->left || !root->right) {
                root = (root->left) ? root->left : root->right;
            }
            else {
                // both left and right exist, root=min of right
                TreeNode * cur = root->right;
                while (cur->left) cur = cur->left;
                root->val =  cur->val;
                root->right = deleteNode(root->right, cur->val);
            }
        }
        return root;
    }
};

// #################### hace parent pointer ##################################

struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

bool deletNode(TreeNode * root, int key) {
    if (!root) return false;  // corner case

    if (root->val < key) { // key on the right?
        return deletNode(root->right, key);
    }
    else if (root->val > key) { // key on the left ?
        return deletNode(root->left, key);
    }
    else {
        // case 1: leaf node
        if (!root->left && !root->right) {
            // 20 , 40
            // parent 30 : 20 left, 40 right
            TreeNode * tmp = root;
            if (root == root->parent->left) {
                root->parent->left = nullptr;
            }
            else {
                root->parent->right = nullptr;
            }
            delete tmp; // free memory of deleted node
        }

        // case 2: only have left tree
        if (!root->right && root->left) { 
            if (root == root->parent->left) {
                root->parent->left =  root->left;
            }
            else {
                root->parent->right =  root->left;
            }
        }

        // case 3: if have right tree 
        if (root->right) {
            TreeNode * miniSucc = root->right;

            while (miniSucc->left) miniSucc = miniSucc->left;

            root->val =  miniSucc->val;

            delete miniSucc;
        }
        return true;
    }

    return false;

}



