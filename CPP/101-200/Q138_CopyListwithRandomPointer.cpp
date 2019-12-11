/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        unordered_map<Node*, Node*> m; // oldnode--newnode
        Node * res = new Node (head->val, nullptr, nullptr);
        Node * oldNode = head->next, * newNode = res;
        m[head] = res;
        while (oldNode) { // copy nodes, and consturct map for random ptr
            Node * t = new Node(oldNode->val, nullptr, nullptr);
            newNode->next = t;
            m[oldNode] = t;
            oldNode = oldNode->next;
            newNode = newNode->next;
        }
        oldNode = head; newNode = res;
        while (oldNode) { // precess random ptr
            newNode->random = m[oldNode->random];
            oldNode = oldNode->next;
            newNode = newNode->next;
        }
        return res;
    }
};