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
        if (!node) return NULL;
        unordered_map<Node*, Node*> m;  // orig--clone
        queue<Node*> q{{node}};
        Node * clone = new Node(node->val);
        m[node] = clone;
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                for (auto neighbor : t->neighbors) {
                    if (!m.count(neighbor)) {
                        m[neighbor] = new Node(neighbor->val); // clone neighbor
                        q.push(neighbor); // add orig neighbor to queue
                    }
                    m[t]->neighbors.push_back(m[neighbor]); //add neighbor of cloned node
                }                
            }
        }
        return clone;
    }
};