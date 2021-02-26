// Given an array a that contains only numbers in the range from 1 to a.length
// find the first duplicate number for which the second occurrence has the minimal index
// Time O(n), Space O(1)
// Input a = [2, 3, 4, 5, 4, 1, 3, 5, 2], firstDuplicate(a) = 4.
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time O(n), Space O(n)
int firstDuplicate_1(vector<int> a) { 
    vector<int> m (a.size() + 1, 0);
    for (int v : a) {
        if (m[v]) return v;
        else m[v] = v;
    }
    return -1;
}

// Time O(n), Space O(1)
int firstDuplicate_2(vector<int> a) {
    for (int v : a) {
        // 1 <= a[i] <= a.length
        if (a[abs(v) - 1] < 0) return abs(v);
        a[abs(v) - 1] *= -1;
    }
    return -1;
}

int main() {
    vector<int> a = {2, 3, 4, 5, 4, 1, 3, 5, 2};
    
    cout << firstDuplicate_1(a) << endl;
    cout << firstDuplicate_2(a) << endl;
    return 0;
}
