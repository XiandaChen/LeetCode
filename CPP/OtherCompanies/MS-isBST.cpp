#include <iostream>
#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;
};

// 98. Validate Binary Search Tree
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        
        return helper(root, LONG_MAX, LONG_MIN);
    }
    
    bool helper(TreeNode * root, long maxPath, long minPath) {
        if (!root) return true;

        if (root->val <= minPath || root->val >= maxPath) return false;  // NOTE, <=
                
        return helper(root->left, root->val, minPath)
            && helper(root->right, maxPath, root->val);

     }
};


/*

Invalid tree - mismatch with parent 

invalid node: leaf
             10
           /    \
          7      15
        /   \   /  \
       8    9  13  18

invalid node : non-leaf
            10
           /    \
          9      15
        /   \   /  \
       8    7  13  18

            12                // maxPath=INT_MIN, minPath=INT_MAX ==> maxPath=12, minPath=left-val(12)
           /   \
          11     15          // 15: maxPath=12, minPath=12 ==> maxPath=15, minPath=left-val(12)
        /       /  \
       9       13  18       // 13: maxPath=15, minPath=left-val(12) ==> maxPath=15, minPath=left-val(12)
      /  \          / \
     8   13         17        // 17: maxPath=18, minPath=left-val(12) 

// condition 1: left->val < cur->val
// condition 2: cur->val < right->val
// condition 3: cur->val < maxPath & right->val < maxPath
                cur->val > minPath & left->val < minPath

                // update maxPath, minPath

             10
           /    \
          7      15
        /   \   /  \
       8    9  13  18

*/

int main() {
    // you can write to stdout for debugging purposes, e.g.
    std::cout << "This is a debug message" << std::endl;

    return 0;
}
