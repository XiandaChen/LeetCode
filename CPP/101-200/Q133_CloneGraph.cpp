class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        unordered_map<Node*, Node*> m; // orignode-clonenode
        Node * clone = new Node(node->val);
        m[node] = clone;
        queue<Node*> q{{node}}; // BFS graph traversal
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                for (auto neighbor : t->neighbors) {
                    if (!m.count(neighbor)) {
                        m[neighbor] = new Node(neighbor->val); // clone neighbor
                        q.push(neighbor); // add orig neighbor to queue
                    }
                    //add neighbor of cloned node
					// vector<Node*> neighbors;
                    m[t]->neighbors.push_back(m[neighbor]);
                }
            }
        }
        return clone;
    }
};