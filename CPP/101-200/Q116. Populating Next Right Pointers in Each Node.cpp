class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return NULL;
        queue<Node*> q{{root}};
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
                if (i == 1) {
                    t->next = NULL;
                }
                else {
                    t->next = q.front();
                }
            }
        }
        return root;
    }
};