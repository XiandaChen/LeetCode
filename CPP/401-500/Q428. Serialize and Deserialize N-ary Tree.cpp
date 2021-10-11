class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (!root) return "#";  // NOTE, "#"
        
        queue<Node*> q {{root}};
        string res = "";
        
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            
            // NOTE, children size to seperate nodes
            res += to_string(t->val) + " " + to_string(t->children.size()) + " ";
            
            for (auto & a : t->children) {
                q.push(a);
            }
        }
        
        return res;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if (data.empty()) return nullptr;  
        
        istringstream is(data);
        string val, size;
        
        is >> val;
        if (val == "#") return nullptr;

        is >> size;
        Node * res = new Node(stoi(val), {}), * root = res;
        
        queue<Node*> qNode{{root}};
        queue<int> qSize{{stoi(size)}};
        
        while (!qNode.empty()) {
            auto t = qNode.front(); qNode.pop();
            int len = qSize.front(); qSize.pop();
            
            for (int i = 0; i < len; i++) {
                if (!(is >> val)) break;
                if (!(is >> size)) break;
                
                Node * node = new Node(stoi(val), {});
                qNode.push(node);
                
                qSize.push(stoi(size));
                
                // NOTE: add child nodes
                t->children.push_back(node);
            }
            
        }
        
        return res;
    }
};