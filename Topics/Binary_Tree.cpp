// 94. Binary Tree Inorder Traversal
// Using Recursion/DFS
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorderTraversalDFS(root, res);
        return res;
    }
    void inorderTraversalDFS(TreeNode* root, vector<int>& res) {
        if (!root) return;
        if (root->left) inorderTraversalDFS(root->left, res);
        res.push_back(root->val);
        if (root->right) inorderTraversalDFS(root->right, res);
    }
};
// 94. Binary Tree Inorder Traversal
// Input: root = [1,null,2,3]; Output: [1,3,2]
// Using Stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* p = root;
        while (p || !st.empty()) {
            while (p) {
                st.push(p);
                p = p->left;
            }
            p = st.top(); st.pop();
            res.push_back(p->val);
            p = p->right;
        }
        return res;
    }
};

// 95. Unique Binary Search Trees II
// DC, similar to Q241


// 96. Unique Binary Search Trees
// Catalan Number
// dp[i]: number of unique BST that store values 1,..,i
// dp[i] += dp[j] * dp[i -1 - j]
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1); // dp[n] for n
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)
                dp[i] += dp[j] * dp[i -1 - j]; //
        return dp.back();
    }
};

// 95. Unique Binary Search Trees II
// Given an integer n, generate all structurally unique BST's that store values 1 ... n.
// DC
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) return {nullptr};  // vector {nullptr}
        vector<TreeNode*> res;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> left = generateTrees(start, i - 1);   // divide
            vector<TreeNode*> right = generateTrees(i + 1, end);
            for (auto a : left) {   // conque
                for (auto b : right) {
                    TreeNode* node = new TreeNode(i);
                    node->left = a;
                    node->right = b;
                    res.push_back(node);
                }
            }
        }
        return res;
    }
};

// 144. Binary Tree Preorder Traversal
// Using Stack
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) return{};
        vector<int> res;
        stack<TreeNode*> st{{root}};
        while (!st.empty()) {
            TreeNode * t = st.top();
            st.pop();
            res.push_back(t->val);
            if (t->right) st.push(t->right);
            if (t->left) st.push(t->left);
        }
        return res;
    }
};

// 145. Binary Tree Postorder Traversal
// Using Stack
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {}; // must to prevent access null pointer at line 19
        vector<int> res;
        stack<TreeNode*> st{{root}};
        TreeNode * pre = root; // pre: node pre-added to res
        while (!st.empty()) {
            TreeNode * t = st.top();
            if ((!t->left && !t->right) || t->left == pre || t->right == pre) {
                res.push_back(t->val);
                st.pop();
                pre = t;
            }
            else {
                if (t->right) st.push(t->right);
                if (t->left) st.push(t->left);
            }
        }
        return res;
    }
};

// 102. Binary Tree Level Order Traversal
// Extend: Q199 Binary Tree Right Side View
//		   Q103 Binary Tree Zigzag Level Order Traversal
// DFS
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        levelOrder(root, 0, res);
        return res;
    }
    void levelOrder(TreeNode * root, int level, vector<vector<int>> & res) {
        if (!root) return;
        if (res.size() == level) res.push_back({}); // new level
        res[level].push_back(root->val);
        if (root->left) levelOrder(root->left, level + 1, res);
        if (root->right) levelOrder(root->right, level + 1, res);
    }
};
// 102. Binary Tree Level Order Traversal
// BFS, using queue
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            vector<int> onelevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();  // queue: front(); stack: top()
                onelevel.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(onelevel);
        }
        return res;
    }
};

// 987. Vertical Order Traversal of a Binary Tree
// When two nodes have the same position, sort them  based on the nodes' values
// For each node at (X, Y), its left and right children: (X-1, Y-1) and (X+1, Y-1)
// Input: [3,9,20,null,null,15,7];    Output: [[9],[3,15],[20],[7]]
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        map<int, vector<pair<int, int>>> m; // x-[<y, val>..]
        dfs(root, 0, 0, m); // node map
        vector<vector<int>> res;
        for (auto a : m) {
            vector<int> col;
            sort(a.second.begin(), a.second.end()); // sort vector using y's
            for (int i = 0; i < a.second.size(); ++i)
                col.push_back(a.second[i].second);
            res.push_back(col);
        }
        return res;
    }
    void dfs(TreeNode * node, int x, int y, map<int, vector<pair<int, int>>> & m) {
        if (!node) return;
        // by default, sort() in increasing order, need to use "-y" to sort decreasing
        m[x].push_back(make_pair(-y, node->val)); 
        dfs(node->left, x - 1, y - 1, m);
        dfs(node->right, x + 1, y - 1, m);
    }
};

// 314. Binary Tree Vertical Order Traversal
// When two nodes have the same position, sort them based on X ("from left to right")
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        // root order: 0; left: -1; right: +1
        map<int, vector<int>> m; // vertical order--nodes
        queue<pair<int, TreeNode*>> q;  // order-node*
        q.push({0, root});
        
        // level order traversal
        while (!q.empty()) {
            auto a = q.front(); q.pop();
            m[a.first].push_back(a.second->val);
            if (a.second->left) q.push({a.first - 1, a.second->left});
            if (a.second->right) q.push({a.first + 1, a.second->right});
        }
        
        for (auto a : m) res.push_back(a.second);
        
        return res;
    }
};

// 270. Closest Binary Search Tree Value
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int res = root->val;
        while (root) {
            if (abs(res - target) > abs(root->val - target))
                res = root->val;
			// binary search tree: left < root < right
            root = (root->val > target) ? root->left : root->right; 
        }
        return res;
    }
};

// 958. Check Completeness of a Binary Tree
// BFS, using queue  (difficult to write DFS version)
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q({root});
        while (!q.empty()) {
            TreeNode * t = q.front(); q.pop();
            if (!t) break;      // stop when meeting null node
            q.push(t->left);
            q.push(t->right);
        }
        while (!q.empty()) { // if non-null node exist
            TreeNode * t = q.front(); q.pop();
            if (t) return false;
        }
        return true;
    }
};

// 426. Convert Binary Search Tree to Sorted Doubly Linked List
// Using Recursion/DFS
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return NULL;  // don't forget to check NULL
        Node * pre = NULL, * head = NULL; // head: left-most node
        inorderTraversal(root, pre, head);
        head->left = pre;   // doubly-liked list
        pre->right = head;
        return head;
    }
    void inorderTraversal(Node * node, Node *& pre, Node *& head) {
        // binary tree inorder traversal
        if (!node) return;
        inorderTraversal(node->left, pre, head);
        if (!head) { // access left-most node
            head = node;
            pre = node;
        }
        else {
            pre->right = node;
            node->left = pre;
            pre = node;
        }
        inorderTraversal(node->right, pre, head);
    }
};

// 297. Serialize and Deserialize Binary Tree
// Serialize binary tree to a string, and this string can be deserialized to original tree
// Preorder traversal + queue
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
            if (!(iss >> val)) continue; // 
            if (val != "#") { // not '#'
                TreeNode * node = new TreeNode(stoi(val));
                t->left = node;
                q.push(node);  // not forget to add
            }
            // read next value for right node
            if (!(iss >> val)) continue; 
            if (val != "#") {
                TreeNode * node = new TreeNode(stoi(val));
                t->right = node;
                q.push(node);   // not forget to add
            }
        }
        return res;
    }
};

// 863. All Nodes Distance K in Binary Tree
// Return a list of the values of all nodes that have a distance K from the target node
// DFS (Graph traversal)
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root) return {};
        vector<int> res;
        unordered_map<TreeNode*, TreeNode*> parent; // node's parent
        unordered_set<TreeNode*> visited; // to hold visited nodes
        findParent(root, parent);
        helper(target, K, parent, visited, res);
        return res;
    }
    void findParent(TreeNode * node, unordered_map<TreeNode*, TreeNode*> & parent) {
        if (!node) return;
        if (node->left) {
            parent[node->left] = node;
            findParent(node->left, parent);
        }
        if (node->right) {
            parent[node->right] = node;
            findParent(node->right, parent);
        }
    }
    void helper(TreeNode * node, int K, unordered_map<TreeNode*, TreeNode*> & parent, 
               unordered_set<TreeNode*> & visited, vector<int> & res) {
        if (!node || visited.count(node)) return; // if node is null, or had been visited
        visited.insert(node);   // been visited
        if (K == 0) {res.push_back(node->val); return;}
        if (node->left) helper(node->left, K - 1 , parent, visited, res); // left
        if (node->right) helper(node->right, K - 1, parent, visited, res); // right
        if (parent[node]) helper(parent[node], K - 1, parent, visited, res); // parent
    }
};

// 785. Is Graph Bipartite? DFS
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // 0: not accessed, -1/1: diff colors
        vector<int> colors(graph.size(), 0);
        for (int i = 0; i < graph.size(); ++i) { // traverse all nodes
            if (colors[i] == 0 && !isValid(graph, colors, i, 1)) return false;
        }
        return true;
    }
    bool isValid(vector<vector<int>>& graph, vector<int> & colors, int i, int color) {
        // node cur had been colored, with valid color
        if (colors[i] != 0) return colors[i] == color;
        colors[i] = color;
        for (int neighbor : graph[i]) { // color neighbors with diff color
            if (!isValid(graph, colors, neighbor, -1 * color)) return false;
        }
        return true;
    }
};
// 785. Is Graph Bipartite?  
// BFS + queue
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> colors(graph.size()); // 0: not accessed, -1/1: diff colors
        for (int i = 0; i < graph.size(); ++i) { // traverse all nodes
            if (colors[i] != 0) continue; // had been colored
            colors[i] = 1; // color 1
            queue<int> q{{i}}; // neighbors
            while (!q.empty()) {
                int t = q.front(); q.pop();
                for (auto a : graph[t]) {
                    if (colors[a] == colors[t]) return false; // node of an edge have same color
                    if (colors[a] == 0) { // node a have not been colored
                        colors[a] = -1 * colors[t]; // diff color
                        q.push(a); // BFS queue
                    }
                }
            }
        }
        return true;
    }
};

// 98. Validate Binary Search Tree
// Recursion
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // long to cover int edge case: 2147483647
        return isValidBST(root, LONG_MIN, LONG_MAX); 
    }
    bool isValidBST(TreeNode * node, long mn, long mx) {
        if (!node) return true;
        if (node->val <= mn || node->val >= mx) return false;
        return isValidBST(node->left, mn, node->val) 
            && isValidBST(node->right, node->val, mx);
    }
};
// Stack: inorder traversal
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        stack<TreeNode*> st;
        TreeNode * p = root, * pre = NULL;
        while (p || !st.empty()) { // inorder traversal
            while (p) { // left
                st.push(p);
                p = p->left;
            }
            p = st.top(); st.pop(); // mid
            if (pre && p->val <= pre->val) return false; // logic, must be <=
            pre = p;
            p = p->right; // right
        }
        return true;
    }
};

// 114. Flatten Binary Tree to Linked List
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode * cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode * tmp = cur->left;
                while (tmp->right) // right-most child of cur->left
                    tmp = tmp->right; 
                tmp->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL; // must
            }
            cur = cur->right;
        }
    }
};

// 124. Binary Tree Maximum Path Sum
// Given a non-empty binary tree, find the maximum path sum.
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }
    // maxsum of path from cur node to a leaf 
    int dfs (TreeNode * node, int & res) {
        if (!node) return 0;
        // maxsum of node->left
        int left = max(dfs(node->left, res), 0);  // consider the path only if sum>=0
        int right = max(dfs(node->right, res), 0); // right
        res = max(res, left + right + node->val);
        return max(left, right) + node->val; // one path: only max(left, right)
    }
};

// 199. Binary Tree Right Side View
// ref. Q102, level order traversal
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q{{root}}; // level order traversal
        while (!q.empty()) {
            // add the value of right-most node in last level
            res.push_back(q.back()->val);
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop(); // queue-front, stack-top
                if (t->left) q.push(t->left); // first
                if (t->right) q.push(t->right); // last
            }
        }
        return res;
    }
};


// 236. Lowest Common Ancestor of a Binary Tree, Recursion
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || p == root || q == root) return root;
        TreeNode * left = lowestCommonAncestor(root->left, p, q);
        TreeNode * right = lowestCommonAncestor(root->right, p, q);
        // if ancestor for p/q in root->left (root->right)
        if (left && right) return root;
        // // common ancestor for p&q in only left(or right)
        return left ? left : right;
    }
};

// 257. Binary Tree Paths, DFS
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return {};
        vector<string> res;
        dfs(root, "", res);
        return res;
    }
    void dfs(TreeNode * node, string out, vector<string> & res) {
        if (!node->left && !node->right) 
            res.push_back(out + to_string(node->val));
        if (node->left) 
            dfs(node->left, out + to_string(node->val) + "->", res);
        if (node->right)
            dfs(node->right, out + to_string(node->val) + "->", res);
    }
};

// 112. Path Sum, DFS
// Determine if the tree has a root-to-leaf path that sum equals to given value
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        // found a path to a leaf, and nodeVal==remainingSum
        if (!root->left && !root->right && root->val == sum) return true;
        return hasPathSum(root->left, sum - root->val) 
            || hasPathSum(root->right, sum - root->val);
    }
};
// 113. Path Sum II, DFS, find all root-to-leaf path sum equals to given value
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return {};
        vector<vector<int>> res;
        vector<int> out;
        dfs(root, sum, out, res);
        return res;
    }
    void dfs(TreeNode * node, int sum, vector<int> & out, vector<vector<int>> & res) {
        if (!node) return;
        out.push_back(node->val); // must
        if (!node->left && !node->right && node->val == sum)
            res.push_back(out);
        if (node->left)
            dfs(node->left, sum - node->val, out, res);
        if (node->right)
            dfs(node->right, sum - node->val, out, res);
        out.pop_back(); // must
    }
};

// 543. Diameter of Binary Tree
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        dfs(root, res);
        return res;
    }
    // return lenght of longest path from node to a leaf
    int dfs(TreeNode* node, int & res) {
        if (!node) return 0;
        int left = dfs(node->left, res);
        int right = dfs(node->right, res);
        res = max(res, left + right);
        return max(left, right) + 1;
    }
};

// 285. Inorder Successor in BST
// Input: root = [2,1,3], p = 1; Output: 2
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode * res = NULL;
        while (root) {
            if (root->val > p->val) { // root > p
                res = root;
                root = root->left;
            }
            else root = root->right;
        }
        return res;
    }
};

// 510. Inorder Successor in BST II
/*
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/
class Solution {
public:
    Node* inorderSuccessor(Node* node) {
        // inorder successor can be parent, right, or null
        // for node, if having right child => leftmost of right-child
        // if no having right child => firstlarger parent (or grandparent..)
        if (!node) return nullptr;
        Node * res = nullptr;
        if (node->right) {
            res = node->right;
            while (res && res->left) res = res->left;
        }
        else {
            res = node->parent;
            while (res && res->val < node->val) res = res->parent;
        }
        return res;
    }
};

// 653. Two Sum IV - Input is a BST
	// method 2: BST inorder traversal, then two sum in sorted array
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> st;
        return helper(root, k, st);
    }
    bool helper(TreeNode * node, int k, unordered_set<int> & st) {
        if (!node) return false;
        if (st.count(k - node->val)) return true;
        st.insert(node->val);
        return helper(node->left, k, st) || helper(node->right, k, st);
    }
};

// 450
// remove element from binary tree
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // left/right not exist, root=right/left
            // left & right not exist, root=null
            if (!root->left || !root->right) {
                root = (root->left) ? root->left : root->right;
            }
            else {
                // both left and right exist, root=min of right
                TreeNode * cur = root->right;
                while (cur->left) cur = cur->left;
                root->val =  cur->val;
                root->right = deleteNode(root->right, cur->val);
            }
        }
        return root;
    }
};
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        if (root->val == key) {
            if (!root->right) return root->left;
            else {
                TreeNode *cur = root->right;
                while (cur->left) cur = cur->left;
                swap(root->val, cur->val);
            }
        }
        root->left = deleteNode(root->left, key);
        root->right = deleteNode(root->right, key);
        return root;
    }
};

// 1973. Count Nodes Equal to Sum of Descendants
class Solution {
public:
    int equalToDescendants(TreeNode* root) {
        int res = 0;
        treeSum(root, res);
        return res;
    }
    // sum of the tree rooted at node
    long long treeSum(TreeNode * node, int & res) {
        if (!node) return 0;
        long long lsum = treeSum(node->left, res);
        long long rsum = treeSum(node->right, res);
        if ((lsum + rsum) == node->val) res++;
        return (lsum + rsum + node->val);
    }
};