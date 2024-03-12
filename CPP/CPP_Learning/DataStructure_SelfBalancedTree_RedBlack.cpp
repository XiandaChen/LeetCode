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

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;

    Node(T value)
        : data(value), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;

    // Helper functions for insertion and balancing
    void leftRotate(Node<T>*&);
    void rightRotate(Node<T>*&);
    void insertFixup(Node<T>*&);
    void inorderTraversalHelper(Node<T>*);

public:
    RedBlackTree() : root(nullptr) {}

    // Public insert function
    void insert(T);

    // Public inorder traversal function
    void inorderTraversal();
};

// Helper function to perform a left rotation
template <typename T>
void RedBlackTree<T>::leftRotate(Node<T>*& x) {
    Node<T>* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Helper function to perform a right rotation
template <typename T>
void RedBlackTree<T>::rightRotate(Node<T>*& y) {
    Node<T>* x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Helper function for fixing the tree after insertion
template <typename T>
void RedBlackTree<T>::insertFixup(Node<T>*& z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node<T>* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node<T>* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Public insert function
template <typename T>
void RedBlackTree<T>::insert(T value) {
    Node<T>* z = new Node<T>(value);
    Node<T>* y = nullptr;
    Node<T>* x = root;

    while (x != nullptr) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == nullptr)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFixup(z);
}

// Helper function for in-order traversal
template <typename T>
void RedBlackTree<T>::inorderTraversalHelper(Node<T>* root) {
    if (root != nullptr) {
        inorderTraversalHelper(root->left);
        std::cout << root->data << " ";
        inorderTraversalHelper(root->right);
    }
}

// Public inorder traversal function
template <typename T>
void RedBlackTree<T>::inorderTraversal() {
    inorderTraversalHelper(root);
    std::cout << std::endl;
}

int main() {
    RedBlackTree<int> rbTree;

    // Insert values into the Red-Black Tree
    rbTree.insert(10);
    rbTree.insert(20);
    rbTree.insert(30);
    rbTree.insert(15);
    rbTree.insert(25);

    // Perform in-order traversal to display the sorted elements
    std::cout << "In-Order Traversal of Red-Black Tree: ";
    rbTree.inorderTraversal();

    return 0;
}
