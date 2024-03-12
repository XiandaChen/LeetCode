/*
A B+ tree (B-plus tree) is a variant of the B-tree data structure that is commonly used in database systems and file systems for indexing and organizing large amounts of data efficiently. B+ trees share several characteristics with B-trees but have some key differences that make them well-suited for specific use cases. Here are the main characteristics of B+ trees:

1. Node Structure:
Like B-trees, B+ trees have internal nodes with multiple children. However, in a B+ tree, the internal nodes store only keys and are used for navigation. Actual data entries are stored in the leaves.
2. Sorted Data in Leaves:
All data entries are stored in the leaves of the B+ tree, and the leaves form a linked list, allowing for efficient sequential access.
The leaves are connected in a linked list, making range queries and sequential access more efficient.
3. No Duplicate Keys in Internal Nodes:
Unlike B-trees, B+ trees do not store duplicate keys in internal nodes. Duplicate keys are only stored in the leaves.
4. Balanced Structure:
B+ trees maintain a balanced structure, ensuring that the height of the tree remains logarithmic. This balance enables efficient search, insertion, and deletion operations.
5. Range Queries:
B+ trees are particularly well-suited for range queries and range scans because data entries are stored in a sorted order in the leaves. Range queries involve traversing the linked list of leaves.
6. Sequential Access:
The linked list of leaves allows for efficient sequential access to all data entries, making B+ trees suitable for scenarios where sequential access is common, such as in file systems or databases.
7. Non-Leaf Nodes Contain Only Keys:
Internal nodes of a B+ tree only contain keys for navigation purposes. The actual data entries are located in the leaves.
8. Use in Databases:
B+ trees are commonly used for indexing in databases. The structure of B+ trees allows for efficient searches, range queries, and sequential access, making them suitable for scenarios where data retrieval is a common operation.
9. Pointer to Next Leaf:
Each leaf node contains a pointer to the next leaf in the linked list, facilitating efficient sequential access.
10. Insertion and Deletion:
Insertions and deletions in a B+ tree involve modifying the internal nodes and maintaining the balanced structure. These operations are performed in logarithmic time.
*/

/*
Octree:
An octree is a tree-like data structure used to describe three-dimensional space (dividing space). Each node of the octree represents a volume element of a cube, and each node has eight child nodes. The volume elements represented by the eight child nodes are added together to equal the volume of the parent node. The general center point is used as the bifurcation center of the node.
*/

/* B+ tree simplified implementation*/
#include <iostream>
#include <vector>
#include <queue>

// Node structure for B+ tree
template <typename KeyType, typename ValueType>
struct BPlusTreeNode {
    std::vector<KeyType> keys;
    std::vector<ValueType> values;
    BPlusTreeNode* parent;
    std::vector<BPlusTreeNode*> children;
    bool isLeaf;

    BPlusTreeNode(bool leaf = false) : parent(nullptr), isLeaf(leaf) {}
};

// B+ tree class
template <typename KeyType, typename ValueType>
class BPlusTree {
private:
    BPlusTreeNode<KeyType, ValueType>* root;
    int order;  // Order of the B+ tree

public:
    BPlusTree(int order) : root(nullptr), order(order) {}

    // Function to search for a key in the B+ tree
    ValueType search(const KeyType& key) {
        // Implement the search operation
        // Return the corresponding value if found, or handle the case when not found
        // This involves traversing the tree from the root to a leaf node where the key might be present
    }

    // Function to insert a key-value pair into the B+ tree
    void insert(const KeyType& key, const ValueType& value) {
        // Implement the insertion operation
        // This involves finding the appropriate leaf node to insert the key-value pair and then potentially splitting nodes to maintain the B+ tree properties
    }

    // Function to print the B+ tree level by level (for visualization)
    void printLevelOrder() const {
        if (root == nullptr) {
            std::cout << "B+ Tree is empty." << std::endl;
            return;
        }

        std::queue<BPlusTreeNode<KeyType, ValueType>*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            int nodesAtCurrentLevel = nodeQueue.size();

            for (int i = 0; i < nodesAtCurrentLevel; ++i) {
                BPlusTreeNode<KeyType, ValueType>* currentNode = nodeQueue.front();
                nodeQueue.pop();

                std::cout << "[ ";
                for (const KeyType& key : currentNode->keys) {
                    std::cout << key << " ";
                }
                std::cout << "] ";

                if (!currentNode->isLeaf) {
                    for (BPlusTreeNode<KeyType, ValueType>* child : currentNode->children) {
                        nodeQueue.push(child);
                    }
                }
            }

            std::cout << std::endl;
        }
    }
};

int main() {
    // Example usage of B+ tree
    BPlusTree<int, std::string> bPlusTree(3); // Order 3 B+ tree

    bPlusTree.insert(10, "Value1");
    bPlusTree.insert(20, "Value2");
    bPlusTree.insert(5, "Value3");
    bPlusTree.insert(6, "Value4");
    bPlusTree.insert(12, "Value5");

    std::cout << "B+ Tree (Level Order):" << std::endl;
    bPlusTree.printLevelOrder();

    // Perform search operations, insertions, deletions, etc.

    return 0;
}
