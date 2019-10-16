// Note that by default C++ creates a max-heap for priority queue 
#include <iostream> 
#include <queue> 
  
using namespace std; 
  
int main () {
    auto cmp = [](auto & a, auto & b) {
            return a > b; // increasing order
        };
        
    priority_queue <int, vector<int>, decltype(cmp)> g(cmp); 
    g.push(10); 
    g.push(30); 
    g.push(20); 
    g.push(5); 
    g.push(1); 
  
    cout << "The priority queue gquiz is : "; 
    while (!g.empty()) 
    { 
        cout << '\t' << g.top(); 
        g.pop(); 
    } 
    cout << '\n';
    return 0; 
} 