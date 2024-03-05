#include <iostream>
#include <algorithm>
#include <set>
#include <queue>

// BruceForce: O(N*K)
void slidingMin_BruceForce(const int* const inputs, int* const outputs, int arrSize, int K)
{
    for (int i = 0; i < arrSize; ++i) {
        int minValue = inputs[i];
        for (int j = i - 1; j >= std::max(i - K + 1, 0); --j) {
            minValue = std::min(minValue, inputs[j]);
        }
        outputs[i] = minValue;
    }
}
// SortedSet: O(N*logK)
void slidingMin_SortedSet(const int* const inputs, int* const outputs, int arrSize, int K)
{
    std::multiset<int> window;
    for (int i = 0; i < arrSize; ++i) {
        window.insert(inputs[i]);
        if (i >= K) window.erase(window.find(inputs[i - K]));
        outputs[i] = *window.begin();
    }
}
// Heap: O(N*logK)
// Heaps empirically perform better than multiset.
void slidingMin_Heap(const int* const inputs, int* const outputs, int arrSize, int K)
{
    std::priority_queue<std::pair<int, int>> window;
    for (int i = 0; i < arrSize; ++i) {
        // use -inputs[i] since priority_queue is by default a max-heap
        // or, std::priority_queue< std::pair<int, int>,
        //     std::vector< std::pair<int, int> >,
        //      std::greater< std::pair<int, int> > >
        window.push(std::make_pair(-inputs[i], i));
        while (window.top().second <= i - K) window.pop();
        outputs[i] = -1 * window.top().first;
    }
}
// Deque: O(N)
void slidingMin_Deque(const int* const inputs, int* const outputs, int arrSize, int K)
{
    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < arrSize; ++i) {
        while (!window.empty() && window.back().first >= inputs[i]) 
            window.pop_back();
        window.push_back(std::make_pair(inputs[i], i));
        while (window.front().second <= i - K)
            window.pop_front();
        outputs[i] = window.front().first;
    }
}

int main() {
    int inputs[] = {4,3,2,1,5,7,6,8,9};
    int arrSize = sizeof(inputs) / sizeof(inputs[0]), K = 3;
    int* outputs = new int[arrSize];
    // slidingMin_BruceForce(inputs, outputs, arrSize, K);
    // slidingMin_SortedSet(inputs, outputs, arrSize, K);
    // slidingMin_Heap(inputs, outputs, arrSize, K);
    slidingMin_Deque(inputs, outputs, arrSize, K);
    for (int i = 0; i < arrSize; i++) {
        std::cout << outputs[i] << " ";
    }
    return 0;
}