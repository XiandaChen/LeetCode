/*
AVL Trees:
1. Balance Criteria:
AVL trees strictly enforce a balance condition where the heights of the left and right subtrees of any node differ by at most one.
Maintaining this stricter balance results in better search performance but can lead to more frequent rotations during insertions and deletions.
2. Balancing Mechanism:
AVL trees use rotations (single or double rotations) to maintain balance after insertions and deletions.
The balancing process ensures that the tree remains strictly balanced, but it can be more computationally expensive compared to Red-Black trees.
3. Performance:
AVL trees generally have slightly faster lookups compared to Red-Black trees due to their stricter balance condition.
The cost of maintaining balance is higher, making AVL trees more suitable for read-heavy workloads where the frequency of updates is lower.
4. Memory Usage:
AVL trees may use more memory to store balance information for each node (height).
The memory overhead associated with AVL trees can be higher compared to Red-Black trees.
5. Use Cases:
Better suited for scenarios where read operations significantly outnumber write operations.
Useful in applications with high-frequency searches and a lower frequency of insertions and deletions.
Examples include databases, file systems, and network routing tables.

Red-Black Trees:
1. Balance Criteria:
Red-Black trees have a more relaxed balance condition compared to AVL trees.
They ensure that the longest path from the root to any leaf is no more than twice as long as the shortest path.
2. Balancing Mechanism:
Red-Black trees use color-coding (red or black) and rotations to maintain balance.
The balancing process is less strict compared to AVL trees, resulting in fewer rotations during updates.
3 .Performance:
Red-Black trees may have slightly slower lookups compared to AVL trees due to the looser balance condition.
However, they tend to perform better for write-heavy workloads because the balancing overhead is lower.
4. Memory Usage:
Red-Black trees generally use less memory compared to AVL trees because they only need one bit of color information per node.
5. Use Cases:
More suitable for scenarios with frequent insertions and deletions.
Commonly used in standard libraries (e.g., C++ STL's std::map and std::set) and applications where a good balance between read and write performance is required.
*/

#include <iostream>
#include <algorithm> // For std::max

// Definition of a binary tree node
template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height; // Height of the subtree rooted at this node

    TreeNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
template <typename T>
int getHeight(TreeNode<T>* node) {
    return (node == nullptr) ? 0 : node->height;
}

// Function to update the height of a node based on its children's heights
template <typename T>
void updateHeight(TreeNode<T>* node) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

// Function to perform a right rotation on a subtree rooted at y
template <typename T>
TreeNode<T>* rotateRight(TreeNode<T>* y) {
    TreeNode<T>* x = y->left;
    TreeNode<T>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x; // New root of the rotated subtree
}

// Function to perform a left rotation on a subtree rooted at x
template <typename T>
TreeNode<T>* rotateLeft(TreeNode<T>* x) {
    TreeNode<T>* y = x->right;
    TreeNode<T>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y; // New root of the rotated subtree
}

// Function to get the balance factor of a node
template <typename T>
int getBalanceFactor(TreeNode<T>* node) {
    return (node == nullptr) ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Function to insert a value into the AVL Tree
template <typename T>
TreeNode<T>* insert(TreeNode<T>* root, T value) {
    // Standard BST insert
    if (root == nullptr) {
        return new TreeNode<T>(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        // Duplicate values are not allowed in this example
        return root;
    }

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor
    int balance = getBalanceFactor(root);

    // Perform rotations if needed to balance the tree
    // Left Left Case
    if (balance > 1 && value < root->left->data) {
        return rotateRight(root);
    }
    // Right Right Case
    if (balance < -1 && value > root->right->data) {
        return rotateLeft(root);
    }
    // Left Right Case
    if (balance > 1 && value > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left Case
    if (balance < -1 && value < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to perform an in-order traversal of the AVL Tree
template <typename T>
void inOrderTraversal(TreeNode<T>* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

int main() {
    // Example usage of AVL Tree
    TreeNode<int>* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Perform in-order traversal to display the sorted elements
    std::cout << "In-Order Traversal of AVL Tree: ";
    inOrderTraversal(root);
    std::cout << std::endl;

    return 0;
}
