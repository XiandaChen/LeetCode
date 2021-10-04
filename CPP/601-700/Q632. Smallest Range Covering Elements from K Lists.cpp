class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        auto cmp = [](pair<int, pair<int, int>> & a, pair<int, pair<int, int>> & b) {
            return a.first > b.first;
        };
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, 
                        decltype(cmp)> q(cmp); // minHeap: val-<arrID, idx>
        int curMax = INT_MIN, n = nums.size(), resLeft, resRight;
        vector<int> arrLen(n);
        
        for (int i = 0; i < n; i++) {
            arrLen[i] = nums[i].size();
            
            if (nums[i][0] > curMax) curMax = nums[i][0];
            q.push({nums[i][0], {i, 0}});
        }
        
        resLeft = q.top().first;
        resRight = curMax;
        
        // queue holds n elems, i.e., covers n arrays
        while (q.size() >= n) { 
            auto t = q.top(); q.pop();
            int arrID = t.second.first, idx = t.second.second;
            
            if ((curMax - t.first < resRight - resLeft)
               || (curMax - t.first == resRight - resLeft && t.first < resLeft)) {
                resLeft = t.first;
                resRight = curMax;
            }
            
            if (idx + 1 < arrLen[arrID]) {
                q.push({nums[arrID][idx + 1], {arrID, idx + 1}});
                if (nums[arrID][idx + 1] > curMax) curMax = nums[arrID][idx + 1];
            }
            // else
        }
        
        return {resLeft, resRight};
    }
};