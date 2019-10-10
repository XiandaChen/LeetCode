/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> m; // orig--clone
        return cloneGraph(node, m);
    }
    Node * cloneGraph(Node * node, unordered_map<Node*, Node*> & m) {
        if (!node) return NULL;
        if (m.count(node)) return m[node];
        Node * clone = new Node(node->val); // clone node
        m[node] = clone; // to indicate node be cloned
        for (auto neighbor : node->neighbors) { // clone neighbors of node
            clone->neighbors.push_back(cloneGraph(neighbor, m));
        }
        return clone;
    }
};