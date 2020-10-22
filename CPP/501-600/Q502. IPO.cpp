class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        priority_queue<pair<int, int>> maxHeap; // profit-capital
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // capital-profit
        for (int i = 0; i < (int)Profits.size(); ++i) {
            minHeap.push(make_pair(Capital[i], Profits[i])); // sort by capital inscending
        }
        for (int i = 0; i < k; ++i) {
            while (!minHeap.empty() && minHeap.top().first <= W) { // projects that available for W capital
                auto t = minHeap.top(); minHeap.pop();
                maxHeap.push(make_pair(t.second, t.first)); // sort by profit descending
            }
            if (maxHeap.empty()) break;
            W += maxHeap.top().first;
            maxHeap.pop(); // at most k distinct projects
        }
        return W;
    }
};