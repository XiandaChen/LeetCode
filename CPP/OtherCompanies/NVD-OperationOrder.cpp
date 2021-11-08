/*
 * Consider a directed graph where nodes can represent tensors
 * or mathematical operations (add, mult, conv, bias etc).
 *
 * Ex : We can visualize most mathematical operations using these graphs:
 * (A * B) + (C * D) = E
 * The nodes are [A, B, C, D, E, Multiplication_1, Multiplication_2, Add_1]
 * The child connections will look like:
 * A -> Multiplication_1
 * B -> Multiplication_1
 * C -> Multiplication_2
 * D -> Multiplication_2
 * Multiplication_1 -> Add_1
 * Multiplication_1 -> Add_1
 * Add -> E
 * 
 * We will be constructing a graph of such nodes
 * and doing a programming problem on this graph.
 *
 * a) Create a struct/class of such a Node. Think about the all the member variables that will be needed in the Node to
 *      to represent an operation/tensor and also represent the structure of the graph.
 *
 * b) If you are given a list of such Nodes with their correct children
 *    connections, can you find out the sequence of computation of these
 *    Nodes. This should model the data dependencies in the nodes.
 *
 *    For example : [Bias (children: [Relu, Sigmoid]), Conv (children: [Bias]), Relu (children: [Y_1]), 
         Sigmoid (children: [Y_2]), X (children: [Conv]), W (children: [Conv]), B (children: [Bias]), Y_1 (no child), Y_2 (no child)]
 *    Answer : [X, W, Conv, B, Bias, Relu, Sigmoid, Y_1, Y_2]
 *
 *    The given example contains a graph with a simple topology. It is expected
 *    that your code generalizes for more complex topologies of graphs.
 *    A good start might be to design your own example with a complex structure
 *    and think about the problem through that example.
*/

//    x   w
//    \   /
//  conv    B
//     \   /
//     bias
//   /   \
//  relu sig
//   \   \
//   Y1   y2
// ==> [X, W, Conv, B, Bias, Relu, Sigmoid, Y_1, Y_2]
// ==> [W, X, Conv, B, Bias, Relu, Sigmoid, Y_1, Y_2]
// ==> [B, W, X, Conv, Bias, Relu, Sigmoid, Y_1, Y_2]

// [X, Conv, B, Bias, Relu, Sigmoid, Y_1, Y_2, W]

/*
 * (A * B) + (C * D) = E
 * The nodes are [A, B, C, D, E, Multiplication_1, Multiplication_2, Add_1]
*/

//     bias
//   /   \
//  relu sig

using namespace std;

struct Node {
    string name;  //uniqu
    vector<Node *> children;   // 
};

// n in the number of nodes in the list
void printComputationOrder(vector<Node*> nodes, int n) {
    // 1: indegrees for each node, 
    // 2: graph relationship: Node** nodes, 
    // 3: queue, holding zero-deg nodes, topo-search
    
    unordered_map<Node*, int> indegrees;
    
    for (auto node : nodes) { // all node names
        indegrees[node] = 0;
    }
    
    for (auto node : nodes) {
        // indegrees[node] = 0;
        for (auto a : node->children) {
            indegrees[a]++;
        }
    }
    
    queue<Node*> q;  // zero-deg node
    
    for (auto a : indegrees) {
        if (a.second == 0) q.push(a.first);
    }
    
    vector<string> res;
    
    // topology search fro zero-deg nodes
    // [B, W, X, Conv, Bias, Relu, Sigmoid, Y_1, Y_2]
    while (!q.empty()) {
        auto t = q.front(); q.pop();
        res.push_back(t->name);  // append result        
        for (auto child : t->children) {
            if (--indegrees[child] == 0) q.push(child);
        }
    }
    
    // [B, W, X, Conv, Bias, Relu, Sigmoid, Y_1, Y_2]
    for (string s : res) {
        cout << s << ",";
    }
    
}

// write a test case for printComputationOrder
int main() {
	
}












