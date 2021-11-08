#include <iostream>
#include <bits/stdc++.h>

struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;
};

/*
   2
  / \
 1  3
*/
bool helper(TreeNode * root, int & maxPath, int & minPath) {
    if (!root) return true;

    if (minPath > root->val || root->val > maxPath) return false;

    bool leftFlag = true, rightFlag = true;
    if (root->left) {
        maxPath = root->val;
        leftFlag &= helper(root->left, maxPath, minPath);
    }

    if (root->right) {
        minPath = root->val;
        rightFlag &= helper(root->right, maxPath, minPath);
    }

    if (root->left && root->right) return leftFlag && rightFlag;
    if (root->left) return leftFlag;
    if (root->right) return rightFlag;

    return true;
}

bool validBST (TreeNode * root) {
    if (!root) return true;

    int maxPath = INT_MAX, minPath = INT_MIN;

    return helper(root, maxPath, minPath);
}



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
