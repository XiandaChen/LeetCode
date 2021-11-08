#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
// #include <st>

using namespace std;


//     A(0,0)
//    /  \     
//   B(-1, 0)    C    
//  /  \  /\
// g    Dh  i   
//       \
//         F
//   A B C G D F
//a b c d f g

// topology sort
[g][b][a d h] [c f] [i]
// 1: indegree
// 2: queue

struct Node {
    string name;  // A
    vector<Node*> children;  // A: {B, C}
};

string printOrder(vector<Node*> & graph) {
    unordered_map<Node*, int> indegrees;

    for (auto parent : graph) {
        indegrees[parent] = 0;
    }

    // incoming edges 
    for (auto parent : graph) {
        for (auto child : parent) indegrees[child]++;
    }

    queue<Node*> q;

    for (auto node : indegrees) {
        if (node.second == 0) q.push(node);  // zero-deg, eg. A
    }

    string res = "";

    while (!q.empty()) {
        auto t = q.front(); q.pop();

        res += t->name;  // print order

        for (auto child : t->children) {
            if (--indegrees[child] == 0) q.push(child);
        }
    }

    return res;

}




int main() {

    return 0;
}
