/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        ostringstream oss;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            TreeNode * t = q.front(); q.pop();
            if (t) {    // for non nullptr
                oss << t->val << ' ';
                q.push(t->left);
                q.push(t->right);
            }
            else {
                oss << "# ";    // not '# '
            }
        }
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        istringstream iss(data);
        string val; // for stoi(), not be "int val"
        iss >> val;
        TreeNode * res = new TreeNode(stoi(val)), * cur = res;
        queue<TreeNode*> q{{cur}};
        while (!q.empty()) {
            TreeNode * t = q.front(); q.pop();
            // read next value for left node
            if (!(iss >> val)) continue; 
            if (val != "#") { // not '#'
                TreeNode * node = new TreeNode(stoi(val));
                t->left = node;
                q.push(node);  // not forget to add to queue
            }
            // read next value for right node
            if (!(iss >> val)) continue; 
            if (val != "#") {
                TreeNode * node = new TreeNode(stoi(val));
                t->right = node;
                q.push(node);   // not forget to add to queue
            }
        }
        return res;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));